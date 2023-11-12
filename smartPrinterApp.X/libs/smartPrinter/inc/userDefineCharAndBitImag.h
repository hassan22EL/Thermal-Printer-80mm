/* 
 * File:   userDefineCharAndBitImag.h
 * Author: hassa
 *
 * Created on August 28, 2023, 6:04 AM
 */

#ifndef USERDEFINECHARANDBITIMAG_H
#define	USERDEFINECHARANDBITIMAG_H
#include <stdint.h>

#include "ImagesMangement.h"

typedef struct {
    uint8_t u8FirstChar;
    uint8_t u8LastChar;
    uint8_t u8UserDefineSelectOrCencelFlag;
    uint8_t u8UserDefineIsCreated;
    uint8_t u8CustomBitmapBuffer[95 * 36];
    uint8_t u8CustomBitmapBufferIndex[95];
    uint16_t u8CurrentCharIndex;
} st_user_def_char_t;

typedef union {
    st_user_def_char_t st_user_defineChar_t;
    st_BitImage_t st_BitImage_t;
} ut_bitImageWithUserDefineChar_t;


extern ut_bitImageWithUserDefineChar_t gutUserBuffer;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  how can Print the user-define char 
 ---------------------------------------------------------------------------------------------------
 * @param : current byte is 
 * 
 * @return : value of the flag of define Char
 *
 */
uint8_t PrintUserDefineGetFont(uint8_t u8char);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get bit map user define char
 ---------------------------------------------------------------------------------------------------
 * @param : char get From Bitmap
 * 
 * @return : Assign Fonts
 *
 */
void getFontWithBitmap(uint8_t code, st_standFont_t *font);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current First char of user define Char
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : the value of the First Char rang {0x20 to 126}
 *
 */
uint8_t getUserDefineCharFirstChar();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : reset value of the flags and byte in user define char
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 *
 */
void userDefineAndBitMap_init();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Remove custome char From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 *
 */
void CencledTheUserDefineCharFromMemeory(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : select or cencel user define char
 ---------------------------------------------------------------------------------------------------
 * @param :value of select or cencel user define char
 * 
 * @return : none
 *
 */
void SelectOrCencelUserDefineChar(uint8_t value);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set the Value
 ---------------------------------------------------------------------------------------------------
 * @param : First char of the data
 * 
 * @return : second char of the data
 *
 */
void loadUserDefineCharBitMapCoumn(uint8_t c1, uint8_t c2, uint8_t y, uint8_t *bitmap);
/*
---------------------------------------------------------------------------------------------------
 * @brief : getNumber Of Data Byte
---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : max number of bytes in char
 *
 */
uint8_t UserDefineChar_NumberDataByte(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : getValue of user define state
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : 0 is not select , 1 is select
 *
 */
uint8_t getStateOFuserDefine(uint8_t u8char);
#endif	/* USERDEFINECHARANDBITIMAG_H */

