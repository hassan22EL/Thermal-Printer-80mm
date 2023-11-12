#include <drv_usb_hw.h>
#include <printer_core.h>



#include "Printhead.h"
#include "escpos.h"
#include "usart.h"
#include "UserStatus.h"
#include <font.h>
#include <string.h>
usb_core_driver usbd_printer;


#define  ESCPOS_PRINTER_BUFFER      4096U


static uint8_t usbd_Write_into_escpos_buffer(uint8_t *buffer, uint8_t len);

int main(void) {
    nvic_priority_group_set(NVIC_PRIGROUP_PRE3_SUB1);
    /*Port B Config*/
    gpio_event_output_disable();
    exti_event_disable(0);
    timer_disable(TIMER2);
    spi_disable(SPI2);
    adc_disable(ADC1);
    usart_disable(USART0);
    rcu_periph_clock_enable(RCU_ADC1);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_AF);
    rcu_periph_clock_enable(RCU_USBFS);
    SysInit();
    SysTickStart();
    escpos_esc_init();
    /*usb config*/
    usb_rcu_config();
    usbd_init(&usbd_printer, USB_CORE_ENUM_FS, &printer_desc, &usbd_printer_cb);
    usb_intr_config();
    usbdRegisterToreadData(usbd_Write_into_escpos_buffer);


    /*escpos*/
    Printer_Speed(350);
    Printer_Deneisty(300);
    while (1) {
        escpos();
        UsbDriver();
    }
}

static uint8_t usbd_Write_into_escpos_buffer(uint8_t *buffer, uint8_t len) {
    if (escpos_write_into_receiveBuffer(buffer, len) == FIFO_NO_SPA) {
        return (0);
    }
    return (1);
}

/*sync Function*/
void systemAppSyncFunc(void) {
    FeedButtonScan();
}
