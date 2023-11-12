/* 
 * File:   flash.h
 * Author: hassa
 *
 * Created on September 5, 2023, 5:08 AM
 */

#ifndef FLASH_H
#define	FLASH_H

#include <stdint.h>

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : user function  
 ---------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Reset all variables in Flash 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void flash_init(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Read Data
 ---------------------------------------------------------------------------------------------------
 *  @param : Pointer  write Buffer
 * 
 * @param : Address of the start Data
 * 
 * @param : number of byte Required
 * 
 * @return:  none
 */
void flash_read_data(uint8_t *pbuffer, uint32_t u32Address, uint32_t u32size);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : write Data
 ---------------------------------------------------------------------------------------------------
 *  @param : Pointer  write Buffer
 * 
 * @param : Address of the start Data
 * 
 * @param : number of byte Required
 * 
 * @return:  none
 */
void flash_write_data(uint8_t *pbuffer, uint32_t u32Address, uint32_t u32size);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get the Flash is Ready Or not
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 is busy , 1 is Ready
 */
uint8_t flash_ready();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get flash last operation state
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  FLASH_TIME_OUT , FLASH_ERROR , FLASH_SUCESS
 */
uint8_t flash_error();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  chip erase
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  FLASH_SUCESS , FLSAH_TIME_OUT , FLSAH_RUNNING ,FLASH_ERROR
 */
void flash_chip_erase(void);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Block erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the block to be erase
 * 
 * @return:  none
 */
void flash_erase_block(uint32_t u32Address);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Sector erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the sector to be erase
 * 
 * @return: none
 */
void flash_erase_sector(uint32_t u32Address);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash Received Data handler
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void isr_spi2_receiver(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : write Status Register
 ---------------------------------------------------------------------------------------------------
 *  @param : Register Number {0 to 2} 
 * 
 * @param :current data to set in Status Register
 * 
 * @return:  none
 */
void flash_write_status_register(uint8_t RegisterNumber, uint8_t value);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash memory background task
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void FlashMemoryDriver();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Sector erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the sector to be erase
 * 
 * @return: none
 */
void flash_write_status_Registers(uint8_t Reg1, uint8_t Reg2, uint8_t Reg3);
#endif	/* FLASH_H */

