/*
 * InterruptHander.h
 *
 *  Created on: Jul 6, 2023
 *      Author: hassa
 */

#ifndef INC_GD32F30X_IT_H_
#define INC_GD32F30X_IT_H_
#include <gd32f30x.h>

/* function declarations */
/* this function handles NMI exception */
void NMI_Handler(void);
/* this function handles HardFault exception */
void HardFault_Handler(void);
/* this function handles MemManage exception */
void MemManage_Handler(void);
/* this function handles BusFault exception */
void BusFault_Handler(void);
/* this function handles UsageFault exception */
void UsageFault_Handler(void);
/* this function handles SVC exception */
void SVC_Handler(void);
/* this function handles DebugMon exception */
void DebugMon_Handler(void);
/* this function handles PendSV exception */
void PendSV_Handler(void);
/* SPI2 handle function */
void SPI2_IRQHandler(void);
/* EXTI5_9 handle Function */
void EXTI5_9_IRQHandler(void);

#endif /* INC_GD32F30X_IT_H_ */
