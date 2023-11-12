/* 
 * File:   PrintHeadResFile.h
 * Author: hassa
 *
 * Created on August 7, 2023, 11:49 AM
 */

#ifndef PRINTHEADRESFILE_H
#define	PRINTHEADRESFILE_H

#include <gd32f30x_gpio.h>
#include <gd32f30x_timer.h>
#include <stdint.h>



#define  FEED_APHASE_PORTx            GPIOC              
#define  FEED_APHASE_PINx             GPIO_PIN_13

#define  FEED_BPHASE_PORTx            GPIOC              
#define  FEED_BPHASE_PINx             GPIO_PIN_14

#define  FEED_ENABLE_PORTx            GPIOC              
#define  FEED_ENABLE_PINx             GPIO_PIN_15


#define  FEED_PHASESPEED_PORTx      GPIOA
#define  FEED_PHASESPEED_PINx       GPIO_PIN_4

#define  FEED_SLEEP_PORTx           GPIOB
#define  FEED_SLEEP_PINx            GPIO_PIN_7


#define   PRINTER_POWER_SW_PORTx    GPIOB
#define   PRINTER_POWER_SW_PINx    GPIO_PIN_14


#define  PRINTER_STB_PORTx          GPIOB
#define  PRINTER_STB_PINx          GPIO_PIN_4


#define  PRINTER_LAT_PORTx          GPIOD
#define  PRINTER_LAT_PINx          GPIO_PIN_2


#define PRINTER_ERROR_LED_PORTx   GPIOB
#define PRINTER_ERROR_LED_PINx    GPIO_PIN_15



#define PRINTER_BUZZER_LED_PORTx      GPIOA
#define PRINTER_BUZZER_LED_PINx       GPIO_PIN_15



#define  STEP_DISTANCE               125U      // .125mm 
#define  STEP_ANGLE                   15U




#define  HEAD_MAX_ROW_SIZE               640U  
#define  HEAD_NBYTE                      80
#define  TOTAL_STEP_PHASE                4




#endif	/* PRINTHEADRESFILE_H */

