#include <gd32f30x_gpio.h>
#include <escpos.h>
#include <font.h>

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : usart  config and reset to be buad rate
 ---------------------------------------------------------------------------------------------------
 * @param : buadrate Generate
 * 
 * @return : none
 */
void usart_config(uint32_t buadrate) {
    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, GPIO_PIN_9);
    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_MAX, GPIO_PIN_10);
    /* configure USART */
    usart_baudrate_set(USART0, buadrate);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
    usart_hardware_flow_cts_config(USART0, USART_CTS_ENABLE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_ENABLE);
    nvic_irq_enable(USART0_IRQn, 0x04, 0x00);
    usart_dma_receive_config(USART0, USART_RECEIVE_DMA_ENABLE);
    usart_interrupt_enable(USART0, USART_INT_RBNE);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : uart Interrupt handler
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
void usart_isr(void) {

    uint8_t ReceiveData;
    ReceiveData = (uint8_t) usart_data_receive(USART0);
    usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);
    (void) escpos_write_into_receiveBuffer(&ReceiveData, 1);
}


