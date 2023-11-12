/* 
 * File:   escpos_cmd.h
 * Author: hassa
 *
 * Created on August 27, 2023, 3:52 PM
 */

#ifndef ESCPOS_CMD_H
#define	ESCPOS_CMD_H
#include <AllFilesInc.h>
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  pointer read data assignment
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void assignPointerOfreceieBuffer(stByteFIFO_t *pointer);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Start Parsing Of The Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
uint8_t escpos_cmd_main(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Init all var in this file
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 
 */
void escpos_cmd_init(void);
#endif	/* ESCPOS_CMD_H */

