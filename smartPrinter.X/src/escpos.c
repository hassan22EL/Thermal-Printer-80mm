
#include <sys/_stdint.h>

#include <escpos.h>
#include <system.h>
#include <gd32f30x_gpio.h>


#include <AllFilesInc.h>
#include <stdint-gcc.h>
#include <string.h>
#include <stdio.h>
#include "cutOperation.h"

typedef struct {
    uint8_t u8ParsingState;
    uint8_t u8PrinterState;
    uint8_t u8PowerOnState;
    uint8_t u8CommIsFullState;
    uint8_t u8Dumstate;
    uint8_t DumpExit;
    uint8_t u8TestModeActive;

} st_escpos_t;



/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Parsing State
 ---------------------------------------------------------------------------------------------------
 */
static st_escpos_t gstEscpos;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Receive Buffer from usb or uart
 ---------------------------------------------------------------------------------------------------
 */
static stByteFIFO_t gstEscPosReceiveBuffer;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Receive Buffer from usb or uart
 ---------------------------------------------------------------------------------------------------
 */
static stByteFIFO_t gstEscPosPrintBuffer;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Receive Buffer array
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t gu8EscPosReceiveBuffer[RECEIVEBUFFERSIZE];
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Receive Buffer array
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t gu8EscPosPrintBuffer[RECEIVEBUFFERSIZE];
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Proto Type Function 
 ---------------------------------------------------------------------------------------------------
 */
static void espos_Process(void);
static void ErrorInitParameter();
static void SystemPowerOn();
static void ReadDataFromReceiveBuffer();
static void DumpMode();
static void Self_Test();

static uint8_t DumpExit(stkey_t *key);
static uint8_t FeedPaper(stkey_t* key);
static uint8_t SelfTestExit(stkey_t *key);
static uint8_t keyPowerOn(stkey_t *key);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Peek D buffer just one byte to buffer
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: ESCPOS STATUS
 */
static void espos_Process(void) {
    uint8_t Cmd;

    switch (gstEscpos.u8ParsingState) {
        case 0:
            if (fifo_byte_Peek(&gstEscPosPrintBuffer, &Cmd, 0) == FIFO_ERR_NO_DAT) {
                return;
            }
            if (Cmd < 0x20) {
                gstEscpos.u8ParsingState = 1;
                return;
            }

            if (Cmd == 0x7F) {
                return;
            }
            /* receive data */
            WriteChar(Cmd);
            break;
        case 1:
            /*start Parsing of the command*/
            if (escpos_cmd_main()) {
                gstEscpos.u8ParsingState = 0;
            }
            break;
        default:
            gstEscpos.u8ParsingState = 0;
            break;
    }

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Init Esc-Pos Function
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: ESCPOS STATUS
 */
static void ErrorInitParameter() {
    ResetCut();
    ResetHead();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Init Esc-Pos Function
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: ESCPOS STATUS
 */
void escpos_esc_init() {
    cut_Init();
    UserStatusInit();
    printhead_init();
    flash_init();
    usart_config(115200U);
    escpos_cmd_init();
    FeedButtonInit();
    CencledTheUserDefineCharFromMemeory();
    ImagesInit();
    assignPointerOfreceieBuffer(&gstEscPosPrintBuffer);
    fifo_bytes_init(&gstEscPosReceiveBuffer, gu8EscPosReceiveBuffer, RECEIVEBUFFERSIZE);
    fifo_bytes_init(&gstEscPosPrintBuffer, gu8EscPosPrintBuffer, RECEIVEBUFFERSIZE);
    PixelBufferInit(576, 192);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    gutDipSwitch.u8DipSwitch = 0x00;
    gstEscpos.u8PowerOnState = 1;
    gstEscpos.u8PrinterState = 1;
    gstEscpos.u8ParsingState = 0;
    gstEscpos.u8Dumstate = 0;
    gstEscpos.u8TestModeActive = 0;

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write data into escpos Receive buffer
 ---------------------------------------------------------------------------------------------------
 * @param : pointer to source data
 * 
 * @param : number of byte copy
 * 
 * @return:none
 */
uint8_t escpos_write_into_receiveBuffer(uint8_t *buf, uint8_t len) {
    return fifo_bytes_write(&gstEscPosReceiveBuffer, buf, len);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
void ReadCurrentCmd() {
    (void) fifo_byte_remove(&gstEscPosPrintBuffer);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  escpos main function
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void escpos(void) {

    if (gstEscpos.u8PrinterState == 0) {
        ReadDataFromReceiveBuffer();
        espos_Process();
        Cutter();
        RunActions();
        DumpMode();
        Self_Test();
    }
    ButtonDriver();
    SystemPowerOn();
    FlashMemoryDriver();
    UserStatusDriver();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  escpos Power On Function
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void SendXon() {
    if (fifo_FreeSpace(&gstEscPosReceiveBuffer) >= 64) {
        /*Send Xoff */
        if (gstEscpos.u8CommIsFullState) {
            usart_data_transmit(USART0, (uint16_t) 0x11);
        } else {

        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  escpos Power On Function
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void SendXoff() {
    if (fifo_FreeSpace(&gstEscPosReceiveBuffer) <= 64) {
        /*Send Xoff */
        if (gstEscpos.u8CommIsFullState) {
            usart_data_transmit(USART0, (uint16_t) 0x13);
        } else {

        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
void SystemGenerateError() {
    ErrorInitParameter();
    gstEscpos.u8PrinterState = 1;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
void SystemClearError() {
    gstEscpos.u8PrinterState = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
static void SystemPowerOn() {

    switch (gstEscpos.u8PowerOnState) {
        case 0:
            break;
        case 1:
            if (upLoadHeaders()) {
                gstEscpos.u8PowerOnState = 2;
                PowerOnState();
                buttonRegisterEvent(keyPowerOn);
            }
            break;
        case 2:
            break;
        case 3:
            /*Buzzer Run */
            if (PowerOffState()) {
                PrintChar(' ');
                PrintChar(0x0A);
                gstEscpos.u8PowerOnState = 0;
                gstEscpos.u8PrinterState = 0;
            }
            break;
        default:
            gstEscpos.u8PowerOnState = 0;
            break;
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  DumpMode
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  DumpMode
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
static void DumpMode() {
    static uint16_t ByteCount[12];
    static uint8_t ByteIndex = 0;
    static uint8_t MaxChar = 0;
    uint8_t Byte;
    uint8_t i;



    switch (gstEscpos.u8Dumstate) {
        case 0:
            break;
        case 1:
            PrintString("Hexadecimal Dump");
            PrintChar(0x0A);
            PrintString("To terminate hexadecimal dump,");
            PrintChar(0x0A);
            PrintString("press FEED button three times.");
            PrintChar(0x0A);
            PrintChar(0x0A);
            ByteIndex = 0;
            MaxChar = (getMaxDotPerLine() / 48);
            gstEscpos.u8Dumstate = 2;
            break;
        case 2:
            if (fifo_FreeSpace(&gstEscPosPrintBuffer) <= 20) {
                return;
            }
            /*Read data From Receive Buffer and Set In Hex and Char*/
            if (fifo_byte_Read(&gstEscPosReceiveBuffer, &Byte) == FIFO_ERR_NO_DAT) {
                if (gstEscpos.DumpExit) {
                    gstEscpos.DumpExit = 0;
                    i = ByteIndex;
                    while (i != 0 && i < MaxChar) {
                        PrintChar(' ');
                        i++;
                    }
                    i = 0;
                    ByteIndex++;
                    while (ByteIndex != 0) {
                        if (ByteCount[i] < 0x20 || ByteCount[i] > 0x7E) {
                            PrintChar('.');
                        } else {
                            PrintChar(ByteCount[i]);
                        }
                        ByteIndex--;
                        i++;
                    }
                    i = 0;
                    ByteIndex = 0;
                    PrintChar(0x0A);
                    PrintString("            ***  completed  *** ");
                    PrintChar(0x0A);
                    PrintChar(0x0A);
                    PrintChar(0x0A);
                    PrintChar(0x0A);
                    PrintChar(0x0A);
                    PrintChar(0x1d);
                    PrintChar(0x56);
                    PrintChar(0x00);
                    buttonRegisterEvent(FeedPaper);
                    gstEscpos.u8Dumstate = 0;
                    return;
                }
                return;
            }

            if (ByteIndex < MaxChar) {
                ByteCount[ByteIndex] = Byte;
                ByteIndex++;
                printHex(Byte);
            } else {
                ByteIndex = 0;
                gstEscpos.u8Dumstate = 3;
            }
            break;
        case 3:
            for (uint8_t i = 0; i < MaxChar; i++) {
                if (ByteCount[i] < 0x20 || ByteCount[i] > 0x7E) {
                    PrintChar('.');
                } else {
                    PrintChar(ByteCount[i]);
                }
            }
            gstEscpos.u8Dumstate = 2;
            PrintChar(0x0A);
            break;
        default:
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < onCall >                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void onCall                                                                   |
 | < @Description       : Press a Call State                                                            |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t FeedPaper(stkey_t *key) {


    if (key->State == KEY_PRESS) {
        if (QueuLineEmpty() == 0) {
            buttonResetTabCounter(key, 1);
            return (1);
        }
        putFeedAction(getLineSpace());
        buttonResetTabCounter(key, 1);
        return (1);
    }

    if (key->State == LONG_TAP) {
        putFeedAction(getLineSpace());
        buttonResetTabCounter(key, 1);
        return (1);
    }


    buttonResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < onCall >                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void onCall                                                                   |
 | < @Description       : Press a Call State                                                            |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyPowerOn(stkey_t *key) {

    if (key->State == LONG_TAP) {

        if (GetStateOfDoor()) {
            gstEscpos.u8Dumstate = 1;
            gstEscpos.u8TestModeActive = 0;
            gstEscpos.u8PowerOnState = 3;
            buttonRegisterEvent(DumpExit);
        } else {
            gstEscpos.u8Dumstate = 0;
            gstEscpos.u8TestModeActive = 1;
            gstEscpos.u8PowerOnState = 3;
            buttonRegisterEvent(SelfTestExit);
        }
        LongNoReapt();
        buttonResetTabCounter(key, 1);
        return (1);
    }

    if (key->State == KEY_RELEASE) {
        gstEscpos.u8Dumstate = 0;
        gstEscpos.u8PowerOnState = 3;
        gstEscpos.u8TestModeActive = 0;
        buttonRegisterEvent(FeedPaper);
        buttonResetTabCounter(key, 1);
        return (1);
    }
    buttonResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < onCall >                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void onCall                                                                   |
 | < @Description       : Press a Call State                                                            |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t DumpExit(stkey_t *key) {
    if (key->State == MULTI_TAP) {
        if (key->TabCounter >= 2) {
            gstEscpos.DumpExit = 1;
            buttonResetTabCounter(key, 0);
            return (1);
        }

        if (key->TabCounter >= 1) {
            if (QueuLineEmpty() == 0) {
                buttonResetTabCounter(key, 0);
                return (1);
            }
            putFeedAction(getLineSpace());
            buttonResetTabCounter(key, 0);
            return (1);
        }
        buttonResetTabCounter(key, 0);
        return (1);
    }
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < onCall >                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void onCall                                                                   |
 | < @Description       : Press a Call State                                                            |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t SelfTestExit(stkey_t *key) {
    buttonResetTabCounter(key, 1);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Feed Paper
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
static void ReadDataFromReceiveBuffer() {

    /*No-Run at Test Mode*/
    if (gstEscpos.u8TestModeActive) {
        return;
    }

    if (gstEscpos.u8Dumstate) {
        return;
    }
    uint8_t Byte;
    if (fifo_byte_Read(&gstEscPosReceiveBuffer, &Byte) == FIFO_ERR_NO_DAT) {
        return;
    }

    (void) fifo_byte_write(&gstEscPosPrintBuffer, Byte);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  printHex
 ---------------------------------------------------------------------------------------------------
 * @param : char to Print
 * 
 * @return: void
 */
void printHex(uint8_t value) {
    uint8_t buf[3];
    buf[0] = value >> 4;
    buf[1] = (value & 0x0F);
    buf[2] = 0x20;
    for (uint8_t i = 0; i < 2; i++) {
        buf[i] += 0x30;
        if (buf[i] > 0x39) {
            buf[i] += 7;
        }
    }
    (void) fifo_bytes_write(&gstEscPosPrintBuffer, buf, 3);


}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print u8 Number
 ---------------------------------------------------------------------------------------------------
 * @param : number 
 * 
 * @return: void
 */
void printu8Number(uint8_t number) {
    uint8_t buf[3];
    uint8_t startPos = u8TOASII(buf, number);
    (void) fifo_bytes_write(&gstEscPosPrintBuffer, buf + startPos, 3 - startPos);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print u16 Number
 ---------------------------------------------------------------------------------------------------
 * @param : number 
 * 
 * @return: void
 */
void printu16Number(uint16_t number) {
    uint8_t buf[5];
    uint8_t startPos = u16TOASII(buf, number);
    (void) fifo_bytes_write(&gstEscPosPrintBuffer, buf + startPos, 5 - startPos);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print u32 Number
 ---------------------------------------------------------------------------------------------------
 * @param : number 
 * 
 * @return: void
 */
void printu32Number(uint32_t number) {
    uint8_t buf[10];
    uint8_t startPos = u32TOASII(buf, number);
    (void) fifo_bytes_write(&gstEscPosPrintBuffer, buf + startPos, 10 - startPos);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print  Char
 ---------------------------------------------------------------------------------------------------
 * @param : char
 * 
 * @return: void
 */
void PrintChar(uint8_t u8Char) {
    /*Auto*/
    if (u8Char == 0x7F) {
        return;
    }
    (void) fifo_bytes_write(&gstEscPosPrintBuffer, &u8Char, 1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print 
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer To constant string
 * 
 * @return: void
 */
void PrintString(const char *string) {
    uint16_t len = strlen(string);
    for (uint16_t i = 0; i < len; i++) {
        PrintChar(string[i]);
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Self Test 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
static void Self_Test() {
    switch (gstEscpos.u8TestModeActive) {
        case 0:
            break;
        case 1:
            PrintString("      ***  Self Test  ***    ");
            PrintChar(0x0A);
            PrintString("Brand    :    Smart Solutions");
            PrintChar(0x0A);
            PrintString("Temp:        ");
            printu8Number(ShowCurrentTemp());
            PrintString("C");
            PrintChar(0x0A);
            PrintString("InterFace:    USB V2.0");
            PrintChar(0x0A);
            PrintString("InterFace:    Serial ");
            switch (gutDipSwitch.buadrate) {
                case 0:
                    PrintString("115200,");
                    break;
                case 1:
                    PrintString("57600,");
                    break;
                case 2:
                    PrintString("38400,");
                    break;
                case 3:
                    PrintString("19200,");
                    break;
                case 4:
                    PrintString("9600,");
                    break;
            }
            PrintString("NONE,8,1");
            PrintChar(0x0A);
            PrintString("BM Mode :     No");
            PrintChar(0x0A);
            PrintString("Cutter :      ");
            if (gutDipSwitch.cutter) {
                PrintString("Yes");
            } else {
                PrintString("No");
            }
            PrintChar(0x0A);

            PrintString("Beeper :      ");
            if (gutDipSwitch.buzzer) {
                PrintString("Yes");
            } else {
                PrintString("No");
            }
            PrintChar(0x0A);
            PrintString("Speed:        ");
            printu16Number(PrintSpeed());
            PrintString("mm/s");
            PrintChar(0x0A);
            PrintString("Temp:        ");
            printu8Number(ShowCurrentTemp());
            PrintString("C");
            PrintChar(0x0A);
            PrintString("Density:      Light");
            PrintChar(0x0A);
            PrintString("Current Code Page  : Page 0");
            PrintChar(0x0A);
            PrintString("Character Per Line : [Font-A : 48],[Font-B: 64] ");
            PrintChar(0x0A);
            PrintString("Chinese Character  :  NO ");
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintString("Code Pages:");
            PrintChar(0x0A);
            PrintString("0:PC437[Std.Europe]      1.Katakana");
            PrintChar(0x0A);
            PrintString("2:PC850[Multilingual]    3.PC860[Protuguese]");
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintString("Character Table :");
            PrintChar(0x0A);

            for (uint8_t j = 0; j < 96; j++) {
                PrintChar(0x20 + j);
            }

            PrintChar(0x0A);
            PrintString("            ***  completed  *** ");
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintChar(0x0A);
            PrintChar(0x1d);
            PrintChar(0x56);
            PrintChar(0x00);
            buttonRegisterEvent(FeedPaper);
            gstEscpos.u8TestModeActive = 0;
            break;
    }
}