/* 
 * File:   usart.h
 * Author: hassa
 *
 * Created on August 10, 2023, 1:14 PM
 */

#ifndef USART_H
#define	USART_H

#include <stdio.h>


/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : uart Interrupt handler
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
void usart_isr(void);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : usart  config and reset to be buad rate
 ---------------------------------------------------------------------------------------------------
 * @param : buadrate Generate
 * 
 * @return : none
 */
void usart_config(uint32_t buadrate);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : usart  config and reset to be buad rate
 ---------------------------------------------------------------------------------------------------
 * @param : buadrate Generate
 * 
 * @return : none
 */
void RunCommand();
#endif	/* USART_H */

