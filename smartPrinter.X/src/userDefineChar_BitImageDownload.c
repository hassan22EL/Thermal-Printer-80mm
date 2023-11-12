
#include <escpos.h>
#include <string.h>
#include "font.h"
#include "userDefineCharAndBitImag.h"
#include <utility.h>
#include <stdio.h>



/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Bit Image downloaded Image and User define Char 
 ---------------------------------------------------------------------------------------------------
 */
ut_bitImageWithUserDefineChar_t gutUserBuffer;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  how can Print the user-define char 
 ---------------------------------------------------------------------------------------------------
 * @param : current byte is 
 * 
 * @return : value of the flag of define Char
 *
 */
uint8_t PrintUserDefineGetFont(uint8_t u8char) {
    uint8_t value = 0;
    uint8_t currentFont = 0;
    value = gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBuffer[u8char - gutUserBuffer.st_user_defineChar_t.u8FirstChar ];
    if (value == 36) {
        currentFont = 0;
    } else if (value == 27) {
        currentFont = 1;
    } else if (value == 16) {
        currentFont = 2;
    }
    return (currentFont);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get bit map user define char
 ---------------------------------------------------------------------------------------------------
 * @param : char get From Bitmap
 * 
 * @return : Assign Fonts
 *
 */
void getFontWithBitmap(uint8_t code, st_standFont_t *font) {
    uint8_t Index = PrintUserDefineGetFont(code);
    font =  getCurrentstandFont(Index);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current First char of user define Char
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : the value of the First Char rang {0x20 to 126}
 *
 */
uint8_t getUserDefineCharFirstChar() {
    return (gutUserBuffer.st_user_defineChar_t.u8FirstChar);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set the Value
 ---------------------------------------------------------------------------------------------------
 * @param : First char of the data
 * 
 * @return : second char of the data
 *
 */
void loadUserDefineCharBitMapCoumn(uint8_t c1, uint8_t c2, uint8_t y, uint8_t *bitmap) {
    uint8_t nMaxChar;
    uint8_t nMaxBytePerChar;
    gutUserBuffer.st_user_defineChar_t.u8UserDefineIsCreated = 1;
    gutUserBuffer.st_user_defineChar_t.u8FirstChar = c1;
    gutUserBuffer.st_user_defineChar_t.u8LastChar = c2;
    nMaxChar = (c2 - c1) + 1;

    if (y == 3) {
        if (getCurrentFont() == 0) {
            nMaxBytePerChar = 36;
        } else if (getCurrentFont() == 1) {
            nMaxBytePerChar = 27;
        } else {
            return;
        }
    } else if (y == 2 && getCurrentFont() == 2) {
        nMaxBytePerChar = 16;
    } else {
        return;
    }
    if (gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex >= (nMaxChar * nMaxBytePerChar)) {
        gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex = 0;
    }

    gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBufferIndex[ gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex ] = nMaxBytePerChar;
    copyBuff(gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBuffer, bitmap, nMaxBytePerChar);
    gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex += gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBufferIndex[ gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex ]; /*Indicate to next char*/
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Remove custome char From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 *
 */
void CencledTheUserDefineCharFromMemeory(void) {
    gutUserBuffer.st_user_defineChar_t.u8FirstChar = 0;
    gutUserBuffer.st_user_defineChar_t.u8LastChar = 0;
    gutUserBuffer.st_user_defineChar_t.u8UserDefineIsCreated = 0;
    gutUserBuffer.st_user_defineChar_t.u8CurrentCharIndex = 0;
    gutUserBuffer.st_user_defineChar_t.u8UserDefineSelectOrCencelFlag = 0;
    setBuff(gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBuffer, 0x00, (36 * 95));
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : select or cencel user define char
 ---------------------------------------------------------------------------------------------------
 * @param :value of select or cencel user define char
 * 
 * @return : none
 *
 */
void SelectOrCencelUserDefineChar(uint8_t value) {
    if (gutUserBuffer.st_user_defineChar_t.u8UserDefineIsCreated == 0) {
        return;
    }
    gutUserBuffer.st_user_defineChar_t.u8UserDefineSelectOrCencelFlag = value & 0x01;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : getNumber Of Data Byte
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : max number of bytes in char
 *
 */
uint8_t UserDefineChar_NumberDataByte(void) {
    uint8_t value;
    if (getCurrentFont() == 0) {
        value = (36);
    }
    if (getCurrentFont() == 1) {
        value = (27);
    }

    if (getCurrentFont() == 2) {
        value = (16);
    }
    return (value);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : getValue of user define state
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : 0 is not select , 1 is select
 *
 */
uint8_t getStateOFuserDefine(uint8_t u8char) {
    if (gutUserBuffer.st_user_defineChar_t.u8UserDefineIsCreated == 0) {
        return (0);
    }

    if (gutUserBuffer.st_user_defineChar_t.u8UserDefineSelectOrCencelFlag == 0) {
        return (0);
    }

    if (gutUserBuffer.st_user_defineChar_t.u8CustomBitmapBufferIndex[u8char - gutUserBuffer.st_user_defineChar_t.u8FirstChar] == 0) {
        return (0);
    }


    return (1);
}