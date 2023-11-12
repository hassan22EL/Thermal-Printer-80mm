/*
 * gd32f30x_it.c
 *
 *  Created on: Jul 9, 2023
 *      Author: hassa
 */

#include <gd32f30x_it.h>
#include <drv_usbd_int.h>

#include "Printhead.h"
#include "usart.h"
#include <xm25qh16b.h>
#include "cutOperation.h"
extern usb_core_driver usbd_printer;
extern uint32_t usbfs_prescaler;



/* local function prototypes ('static') */
static void resume_mcu_clk(void);

/*!
 \brief      this function handles NMI exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void NMI_Handler(void) {
}

/*!
 \brief      this function handles HardFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void HardFault_Handler(void) {
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
 \brief      this function handles MemManage exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void MemManage_Handler(void) {
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1);
}

/*!
 \brief      this function handles BusFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void BusFault_Handler(void) {
    /* if Bus Fault exception occurs, go to infinite loop */
    //    while (1);
}

/*!
 \brief      this function handles UsageFault exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void UsageFault_Handler(void) {
    /* if Usage Fault exception occurs, go to infinite loop */
    //  while (1);
}

/*!
 \brief      this function handles SVC exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void SVC_Handler(void) {
}

/*!
 \brief      this function handles DebugMon exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void DebugMon_Handler(void) {
}

/*!
 \brief      this function handles PendSV exception
 \param[in]  none
 \param[out] none
 \retval     none
 */
void PendSV_Handler(void) {
}

/*!
 \brief      this function handles USBD interrupt
 \param[in]  none
 \param[out] none
 \retval     none
 */
void USBFS_IRQHandler(void) {
    usbd_isr(&usbd_printer);
}

/*!
 \brief      this function handles USBFS wakeup interrupt request.
 \param[in]  none
 \param[out] none
 \retval     none
 */
void USBFS_WKUP_IRQHandler(void) {
    if (usbd_printer.bp.low_power) {
        resume_mcu_clk();

        rcu_usb_clock_config(usbfs_prescaler);

        rcu_periph_clock_enable(RCU_USBFS);

        usb_clock_active(&usbd_printer);
    }

    exti_interrupt_flag_clear(EXTI_18);
}

/*!
 \brief      this function handles Timer2 interrupt request.
 \param[in]  none
 \param[out] none
 \retval     none
 */
void TIMER2_IRQHandler(void) {
    if (RESET != timer_interrupt_flag_get(TIMER2, TIMER_INT_UP)) {
        printhead_timer2_isr();
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_UP);
    }
}

/*!
 \brief      this function handles Timer3 interrupt request.
 \param[in]  none
 \param[out] none
 \retval     none
 */
void TIMER1_IRQHandler(void) {
    if (RESET != timer_interrupt_flag_get(TIMER1, TIMER_INT_UP)) {
        printhead_timer1_isr();
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_UP);
    }
}

/*!
    \brief      this function handles SPI2 Handler exception
    \param[in]  none
    \param[out] none
    \retval     none
 */
void SPI0_IRQHandler(void) {

}

/*!
    \brief      this function handles SPI2 Handler exception
    \param[in]  none
    \param[out] none
    \retval     none
 */
void SPI2_IRQHandler(void) {

    if (RESET != spi_i2s_interrupt_flag_get(SPI2, SPI_I2S_INT_FLAG_RBNE)) {
        isr_spi2_receiver();
        return;
    }

    spi_i2s_interrupt_disable(SPI2, SPI_I2S_INT_TBE);
    spi_i2s_interrupt_disable(SPI2, SPI_I2S_INT_RBNE);
    NVIC_DisableIRQ(SPI2_IRQn);
}

/*!
 \brief      resume mcu clock
 \param[in]  none
 \param[out] none
 \retval     none
 */
static void resume_mcu_clk(void) {
    /* enable HSE */
    rcu_osci_on(RCU_HXTAL);

    /* wait till HSE is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_HXTALSTB));

    /* enable PLL1 */
    rcu_osci_on(RCU_PLL1_CK);

    /* wait till PLL1 is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_PLL1STB));

    /* enable PLL */
    rcu_osci_on(RCU_PLL_CK);

    /* wait till PLL is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_PLLSTB));

    /* select PLL as system clock source */
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);

    /* wait till PLL is used as system clock source */
    while (RCU_SCSS_PLL != rcu_system_clock_source_get());
}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
 */
void USART0_IRQHandler(void) {
    usart_isr();
}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
 */
void EXTI5_9_IRQHandler(void) {
    if (RESET != exti_interrupt_flag_get(EXTI_9)) {
        /*cutter switch operation*/
        cutter_isr();

    }

}