

#include "gd32f30x_spi.h"
#include <AllFilesInc.h>
#include <stdint-gcc.h>
#include <string.h>
#include <standmode.h>
#define MEM_MODE_ACTIVE_COMANDS                 0

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  ESC-POS Command LIST
 ---------------------------------------------------------------------------------------------------
 * @member : HT : Horizontal tab
 * 
 * @member : LF:Print and line feed
 * 
 * @member : CR : Print and carriage return
 * 
 * @member : FF : Print end position label to start printing
 * 
 * @member : ESC : Have a sub set to define
 * 
 * @member : FS  : Bit Map Operations have FS q or FS p 
 * 
 * @member : GS  : Have a sub set to define
 */
typedef enum et_espos_e {
    HT = 0x09,
    LF = 0x0A,
    FF = 0x0C,
    CR = 0x0D,
    DLE = 0x10,
    ESC = 0x1B,
    FS = 0x1C,
    GS = 0x1D,
} et_espos_t;

typedef union {
    uint8_t byte;

    struct {
        unsigned B0 : 1;
        unsigned B1 : 1;
        unsigned B2 : 1;
        unsigned B3 : 1;
        unsigned B4 : 1;
        unsigned B5 : 1;
        unsigned B6 : 1;
        unsigned B7 : 1;
    };

}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Divide the Byte to 8Bit
 ---------------------------------------------------------------------------------------------------
 * @member : Byte value
 * 
 * @member :strcut of the bit 0 to bit 7
 * 
 */
stPrinterModesUnion;

typedef uint8_t(*pfunCmd)(void);

typedef struct {
    uint8_t Code;
    pfunCmd pFun;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Base Data of the Font
 ---------------------------------------------------------------------------------------------------
 * @member : Code of the Command
 * 
 * @member : Pointer to Command Function 
 */

stcommd_code_argments_t;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Command set
 ---------------------------------------------------------------------------------------------------
 */
static stcommd_code_argments_t gstCurrentCommand;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Commands Pointer can be load
 ---------------------------------------------------------------------------------------------------
 */
static const stcommd_code_argments_t *gpstCurrentCommandLoadArray;

typedef struct {
    uint8_t gu8MainState;
    uint8_t gu8CommandListLength;
    uint8_t gu8CurrentCommandState;
    uint8_t gu8CrearTabOrset;
    uint8_t gu8Arg[5];

} st_escpos_commands_t;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Command Main State
 ---------------------------------------------------------------------------------------------------
 */
static st_escpos_commands_t gstescposCommand;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Memory Array Teset
 ---------------------------------------------------------------------------------------------------
 */
#if MEM_MODE_ACTIVE_COMANDS
static uint8_t gu8memPage[8192U];
#endif
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get Current Code of the Main Command
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t SetCurrentCommand(const stcommd_code_argments_t *currentTable, uint8_t Max);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Command Main State
 ---------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Print Command
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t PrinterDefaultCMD(void);

static uint8_t Printer_Print_And_Line_Feed(void);
static uint8_t Printer_Print_And_Carriage_Return(void);
static uint8_t Printer_JMP_TO_NEXT_TAB_Position(void);

static uint8_t Printer_setHorizontal_Tab_Positions(void);
static uint8_t Printer_Feed_N_Dot(void);
static uint8_t Printer_Feed_N_Line(void);
static uint8_t Printer_Toggle_online_offline_mode(void);
static uint8_t Printer_Test_Page(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Line Space Command
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Set_Default_LineSpacing(void);
static uint8_t Printer_Set_LineSpacing(void);
static uint8_t Printer_Select_Justification(void);
static uint8_t Printer_Set_Left_Blank_Margin_With_Dots(void);
static uint8_t Printer_Set_Relative_Print_Position(void);
static uint8_t Printer_Set_Printing_Area_Width(void);
static uint8_t Printer_Set_Absolute_Print_Position(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Character Command
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Select_Print_Modes(void);
static uint8_t Printer_Set_Double_Width_And_Height(void);
static uint8_t Printer_Turn_White_Black_Printing_Mode(void);
static uint8_t Pinter_Turn_90_Clockwise_Rotation_Mode(void);
static uint8_t Printer_Select_Character_Font(void);
static uint8_t Printer_Turn_Strike_Mode(void);
static uint8_t Printer_Select_Bold_Mode(void);
static uint8_t Printer_Set_Space_Between_Chars(void);
static uint8_t Printer_Turn_UpsideDown_Printing_Mode(void);
static uint8_t Printer_Set_Underline_Dots(void);
static uint8_t Printer_Select_UserDefined_Characters(void);
static uint8_t Printer_Define_UserDefined_Characters(void);
static uint8_t Printer_Cencel_UserDefined_Characters(void);
static uint8_t Printer_Select_Internation_Characters(void);
static uint8_t Printer_Select_Character_Code_Table(void);
static uint8_t Printer_Select_Chinese_Mode(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Kanji Character Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Select_Character_Mode(void);
static uint8_t Printer_Set_Print_Mode_Kanji_Characters(void);
static uint8_t Printer_Turn_Underline_Mode_Kanji(void);
static uint8_t Printer_Define_Kanji_Characters(void);
static uint8_t Printer_Set_Left_Right_Side_Kanji_Character(void);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Bit Image  Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Select_BitImage_Mode(void);
static uint8_t Printer_Define_Downloaded_BitImage(void);
static uint8_t Printer_Print_Downloaded_BitImage(void);
static uint8_t Printer_Print_Bitmap(void);
static uint8_t Printer_Print_NV_Bitmap(void);
static uint8_t Printer_Define_NV_Bitmap(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Reset Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Initialize(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Status Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_RealTime_Status_Transmission(void);
static uint8_t Printer_RealTime_Request_To_Printer(void);
static uint8_t Printer_Generate_Pulse_AT_RealTime(void);
static uint8_t Printer_Transmit_Status(void);
static uint8_t Printer_Generate_Pulse(void);
static uint8_t Printer_Enable_Disable_ASB(void);
static uint8_t Printer_Read_ID(void);
static uint8_t Printer_Set_Process_ID(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   BarCode Commands  Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Select_Printing_Position_of_Human_Readable_Characters(void);
static uint8_t Printer_Set_Barcode_Height(void);
static uint8_t Printer_Set_Barcode_Width(void);
static uint8_t Printer_Select_Font_For_HRI_Characters(void);
static uint8_t Printer_Print_Barcode(void);
static uint8_t Printer_Set_Barcode_Printing_Left_Space(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   controls parameter Commands
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t Printer_Select_Cancel_Panel_Button(void);
static uint8_t Printer_Select_Cut_Mode(void);
static uint8_t Printer_Start_End_Macro_Definition(void);
static uint8_t Printer_Execute_Macro(void);
static uint8_t Printer_Set_Beep_Tone(void);
static uint8_t Printer_Cut_Paper(void);
static uint8_t Printer_Select_Chinese_Code_Format(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Page Mode Commands
 ---------------------------------------------------------------------------------------------------
 */
static void Printer_Print_And_Return_To_Standard_Mode_In_Page_mode(void);
static uint8_t Printer_Print_Data_In_mode_Page(void);
static uint8_t Printer_Select_Page_Mode(void);
static uint8_t Printer_Select_Standard_Mode(void);
static uint8_t Printer_Select_Print_Direction_Page_mode(void);
static uint8_t Printer_Set_Printing_Area_Page_Mode(void);
static uint8_t Printer_Print_2D_Barcode(void);
static uint8_t Printer_Turn_Quadruple_Size_Mode(void);
static uint8_t Printer_Feed_Marked_Paper_To_Print_Starting_Position(void);
static uint8_t Printer_Set_Absolute_Vertical_Print_Position_Page_Mode(void);
static uint8_t Printer_Execute_Test_Print(void);
static uint8_t Printer_Select_Counter_Print_Mode(void);
static uint8_t Printer_Select_Count_Mode_A(void);
static uint8_t Printer_Select_Count_Mode_B(void);
static uint8_t Printer_Set_Counter(void);
static uint8_t Printer_Select_2D_Barcode_Type(void);
static uint8_t Printer_Set_Relative_Vertical_Print_Position_Page_Mode(void);
static uint8_t Printer_Print_Counter(void);
static uint8_t Printer_Set_Horizontal_Vertical_Motion_Unit(void);
static uint8_t PrinterMemTest(void);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Main Command Length of sub commands
 ---------------------------------------------------------------------------------------------------
 */
#define DEL_MAX_CMD      3
#define ESC_MAX_CMD      20
#define GS_MAX_CMD       2
#define FS_MAX_CMD       3



static const stcommd_code_argments_t gstDEL_CMD[DEL_MAX_CMD] = {
    {0x04, Printer_RealTime_Status_Transmission},
    {0x05, Printer_RealTime_Request_To_Printer},
    {0x14, Printer_Generate_Pulse_AT_RealTime},
};
static const stcommd_code_argments_t gstESC_CMD[ESC_MAX_CMD] = {
    {0x20, Printer_Set_Space_Between_Chars}, //1
    {0x21, Printer_Select_Print_Modes}, //2
    {0x24, Printer_Set_Absolute_Print_Position}, //3
    {0x25, Printer_Select_UserDefined_Characters}, //4
    {0x26, Printer_Define_UserDefined_Characters}, //5
    {0x2A, Printer_Select_BitImage_Mode}, //6
    {0x2D, Printer_Set_Underline_Dots}, //7
    {0x32, Printer_Set_Default_LineSpacing}, //8
    {0x33, Printer_Set_LineSpacing}, //9
    {0x3F, Printer_Cencel_UserDefined_Characters}, //10
    {0x44, Printer_setHorizontal_Tab_Positions}, //11
    {0x45, Printer_Select_Bold_Mode}, //12
    {0x47, Printer_Turn_Strike_Mode}, //13
    {0x4A, Printer_Feed_N_Dot}, //14
    {0x64, Printer_Feed_N_Line}, //15
    {0x4D, Printer_Select_Character_Font}, //16
    {0x56, Pinter_Turn_90_Clockwise_Rotation_Mode}, //17
    {0x61, Printer_Select_Justification}, //18
    {0x7B, Printer_Turn_UpsideDown_Printing_Mode}, //19
    {0x5C, Printer_Set_Relative_Print_Position}, //20
};


static const stcommd_code_argments_t gstFS_CMD[FS_MAX_CMD] = {
    {0x70, Printer_Print_NV_Bitmap},
    {0x71, Printer_Define_NV_Bitmap},
    {0x72, PrinterMemTest}
};



static const stcommd_code_argments_t gstGS_CMD[GS_MAX_CMD] = {
    {0x21, Printer_Set_Double_Width_And_Height},
    {0x56, Printer_Cut_Paper},
};

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :pointer to   Receive Buffer from usb or uart
 ---------------------------------------------------------------------------------------------------
 */
static stByteFIFO_t *gpstEscPosReceiveBuffer;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Start Parsing Of The Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
uint8_t escpos_cmd_main(void) {
    /*Read Command the current Command*/
    uint8_t Cmd;

    switch (gstescposCommand.gu8MainState) {
        case 0:
            if (fifo_byte_Read(gpstEscPosReceiveBuffer, &Cmd) == FIFO_ERR_NO_DAT) {
                return (1);
            }
            switch (Cmd) {
                case HT:
                    gstCurrentCommand.pFun = Printer_JMP_TO_NEXT_TAB_Position;
                    gstescposCommand.gu8MainState = 2;
                    break;
                case LF:
                    gstCurrentCommand.pFun = Printer_Print_And_Line_Feed;
                    gstescposCommand.gu8MainState = 2;
                    break;
                case FF:
                    PritMAxSize();
                    return (1);
                    break;
                case CR:
                    gstCurrentCommand.pFun = Printer_Print_And_Carriage_Return;
                    gstescposCommand.gu8MainState = 2;
                    break;
                case DLE:
                    gpstCurrentCommandLoadArray = gstDEL_CMD;
                    gstescposCommand.gu8CommandListLength = DEL_MAX_CMD;
                    gstescposCommand.gu8MainState = 1; /*read next byte*/
                    break;
                case ESC:
                    gpstCurrentCommandLoadArray = gstESC_CMD;
                    gstescposCommand.gu8CommandListLength = ESC_MAX_CMD;
                    gstescposCommand.gu8MainState = 1; /*read next byte*/
                    break;
                case FS:
                    gpstCurrentCommandLoadArray = gstFS_CMD;
                    gstescposCommand.gu8CommandListLength = FS_MAX_CMD;
                    gstescposCommand.gu8MainState = 1; /*read next byte*/
                    break;
                case GS:
                    gpstCurrentCommandLoadArray = gstGS_CMD;
                    gstescposCommand.gu8CommandListLength = GS_MAX_CMD;
                    gstescposCommand.gu8MainState = 1; /*read next byte*/
                    break;
                default:
                    return (1);
                    break;
            }
            break;
        case 1:
            if (fifo_byte_Read(gpstEscPosReceiveBuffer, &Cmd) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            gstCurrentCommand.Code = Cmd;
            if (SetCurrentCommand(gpstCurrentCommandLoadArray, gstescposCommand.gu8CommandListLength)) {
                gstescposCommand.gu8MainState = 2;
            } else {
                gstescposCommand.gu8MainState = 0;
                return (1);
            }
            break;
        case 2:
            if (gstCurrentCommand.pFun != NULL) {
                if (gstCurrentCommand.pFun()) {
                    gstCurrentCommand.pFun = PrinterDefaultCMD;
                    gstescposCommand.gu8MainState = 0;
                    return (1);
                }
            } else {
                gstCurrentCommand.pFun = PrinterDefaultCMD;
                gstescposCommand.gu8MainState = 0;
                return (1);
            }
            break;
        default:
            return (1);
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  pointer read data assignment
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void assignPointerOfreceieBuffer(stByteFIFO_t *pointer) {
    gpstEscPosReceiveBuffer = pointer;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Printer Current Line Feed
 ---------------------------------------------------------------------------------------------------
 * @param : none 
 * 
 * @return:none
 */
static uint8_t Printer_Print_And_Line_Feed(void) {
    if (putDataAction()) {
        gstescposCommand.gu8CurrentCommandState = 0;
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Printer Current Line Feed
 ---------------------------------------------------------------------------------------------------
 * @param : none 
 * 
 * @return:none
 */
static uint8_t Printer_Print_And_Carriage_Return(void) {
    if (gutDipSwitch.autolineEnable == 0) {
        return (1);
    }
    return Printer_Print_And_Line_Feed();

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current tap
 ---------------------------------------------------------------------------------------------------
 * @param : none 
 * 
 * @return:none
 */
static uint8_t Printer_JMP_TO_NEXT_TAB_Position(void) {
    /*set x + n*current char size*/
    TabPorcess();
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set space between char call back 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: ESCPOS STATUS {OK , RUN , ERROR}
 */
static uint8_t Printer_Set_Space_Between_Chars(void) {
    if (fifo_byte_Read(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0]) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    setSpaceBetweenChar(gstescposCommand.gu8Arg[0]);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  select user Define Char
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_UserDefined_Characters(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0]) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    SelectOrCencelUserDefineChar(gstescposCommand.gu8Arg[0] & 0x01);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  define user Define Char
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Define_UserDefined_Characters(void) {

    uint8_t CharDatabuffer[36];

    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:

            if (fifo_bytes_peek(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 0, 3) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            if (gstescposCommand.gu8Arg[0] != 3 && gstescposCommand.gu8Arg[0] != 2) {
                return (1);
            }

            if (gstescposCommand.gu8Arg[1] < 0x20 && gstescposCommand.gu8Arg[1] > gstescposCommand.gu8Arg[2]) {
                return (1);
            }

            if (gstescposCommand.gu8Arg[2] > 0x7F) {
                return (1);
            }
            /*remove arg from buffer*/
            (void) fifo_bytes_remove(gpstEscPosReceiveBuffer, 3);
            gstescposCommand.gu8CurrentCommandState = 1;
            break;
        case 1:
            if (fifo_bytes_read(gpstEscPosReceiveBuffer, CharDatabuffer, UserDefineChar_NumberDataByte()) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            gstescposCommand.gu8CurrentCommandState = 0;
            loadUserDefineCharBitMapCoumn(gstescposCommand.gu8Arg[1], gstescposCommand.gu8Arg[2], gstescposCommand.gu8Arg[0], CharDatabuffer);
            return (1);
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set left margin to start Print Line
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_Print_Modes(void) {

    stPrinterModesUnion PrinterMode;
    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    PrinterMode.byte = gstescposCommand.gu8Arg[0];
    setCurrentFont(PrinterMode.B0);
    setCurrentBold(PrinterMode.B3);
    setDrawingSizeY(1 + PrinterMode.B4); /*Double with in */
    setDrawingSizeX(1 + PrinterMode.B5);
    setCurrentUnderLine(PrinterMode.B7);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Line spacing 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Set_LineSpacing(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0]) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    setLineSpace(gstescposCommand.gu8Arg[0]);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Start of the Print Position
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Set_Absolute_Print_Position(void) {
    /*wait for peek 2 Byte*/

    int16_t Absoulute;
    if (fifo_bytes_read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 2) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    Absoulute = (gstescposCommand.gu8Arg[0] + (gstescposCommand.gu8Arg[1] << 8));
    setAbsoluteXPostion(Absoulute);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Number Of Dot of under Line
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Set_Underline_Dots(void) {
    /*wait for peek 1 Byte*/

    if (fifo_byte_Peek(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0], 0) == FIFO_ERR_NO_DAT) {
        return (0);
    }


    if (gstescposCommand.gu8Arg[0] == 0 || gstescposCommand.gu8Arg[0] == 48) {
        setCurrentUnderLine(0);
        ReadCurrentCmd();
        return (1);
    }

    if (gstescposCommand.gu8Arg[0] == 1 || gstescposCommand.gu8Arg[0] == 49) {
        setCurrentUnderLine(1);
        ReadCurrentCmd();
        return (1);
    }
    return (1);
}

static uint8_t Printer_Set_Default_LineSpacing(void) {
    setDefaultLineSpace();
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  read current command From Table of stand command and 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 
 */
static uint8_t SetCurrentCommand(const stcommd_code_argments_t *currentTable, uint8_t Max) {

    for (uint8_t i = 0; i < Max; i++) {
        if (currentTable[i].Code == gstCurrentCommand.Code) {
            gstCurrentCommand.pFun = currentTable[i].pFun;
            return (1);
        }
    }

    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Init all var in this file
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 
 */
void escpos_cmd_init(void) {
    gstescposCommand.gu8MainState = 0;
    gstescposCommand.gu8CommandListLength = 0;
    gpstCurrentCommandLoadArray = 0;
    gstescposCommand.gu8CurrentCommandState = 0;
    gstCurrentCommand.pFun = PrinterDefaultCMD;
}

__attribute__((unused)) static uint8_t Printer_RealTime_Status_Transmission(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_RealTime_Request_To_Printer(void) {
    return (1);


}

__attribute__((unused)) static uint8_t Printer_Generate_Pulse_AT_RealTime(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Create Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_BitImage_Mode(void) {
    uint16_t nByte;
    uint16_t width;

    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:

            if (fifo_bytes_peek(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 0, 3) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            if (gstescposCommand.gu8Arg[2] > 3) {
                return (1);
            }
            /*remove arg from buffer*/
            (void) fifo_bytes_remove(gpstEscPosReceiveBuffer, 3);
            gstescposCommand.gu8CurrentCommandState = 1;
            break;
        case 1:
            width = gstescposCommand.gu8Arg[1] + (gstescposCommand.gu8Arg[2] << 8);
            if (gstescposCommand.gu8Arg[0] == 0 || gstescposCommand.gu8Arg[0] == 1) {
                nByte = width;
            } else if (gstescposCommand.gu8Arg[0] == 32 || gstescposCommand.gu8Arg[0] == 33) {
                nByte = width * 3;
            } else {
                nByte = width;
            }
            if (fifo_UsedSpace(gpstEscPosReceiveBuffer) < nByte) {
                return (0);
            }
            gstescposCommand.gu8CurrentCommandState = 0;
            WriteBitImage(gstescposCommand.gu8Arg[0], width, gpstEscPosReceiveBuffer);
            return (1);
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Create Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Cencel_UserDefined_Characters(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Tab settings
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_setHorizontal_Tab_Positions(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    if (gstescposCommand.gu8Arg[0] != 0) {
        gstescposCommand.gu8CrearTabOrset = 1;
        if (fillTabBuffer(gstescposCommand.gu8Arg[0], gstescposCommand.gu8CurrentCommandState)) {
            gstescposCommand.gu8CurrentCommandState++;
            return (0);
        }
        gstescposCommand.gu8CurrentCommandState = 0;
        Default_Tab_set();
        return (1);
    }
    if (gstescposCommand.gu8CrearTabOrset == 1) {
        gstescposCommand.gu8CrearTabOrset = 0;
        gstescposCommand.gu8CurrentCommandState = 0;
        return (1);
    }
    gstescposCommand.gu8CurrentCommandState = 0;
    Default_Tab_set();
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Bold Options
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_Bold_Mode(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    setCurrentBold(gstescposCommand.gu8Arg[0]);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set strike Options
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Turn_Strike_Mode(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    setDoubleStrike(gstescposCommand.gu8Arg[0] & 0x01);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print and Paper feed 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Feed_N_Dot(void) {
    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:
            if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_OK) {

                if (PrintBufferHasData() == 0) {
                    gstescposCommand.gu8CurrentCommandState = 2;
                } else {
                    gstescposCommand.gu8CurrentCommandState = 1;
                }
            }
            break;
        case 1:
            if (putDataAction()) {
                gstescposCommand.gu8CurrentCommandState = 2;
            }
            break;
        case 2:
            if (gstescposCommand.gu8Arg[0] == 0) {
                gstescposCommand.gu8CurrentCommandState = 0;
                return (1);
            }
            if (putFeedAction(gstescposCommand.gu8Arg[0])) {
                gstescposCommand.gu8CurrentCommandState = 0;
                return (1);
            }
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print and Paper feed 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Feed_N_Line(void) {
    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:
            if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_OK) {

                if (PrintBufferHasData() == 0) {
                    gstescposCommand.gu8CurrentCommandState = 2;
                } else {
                    gstescposCommand.gu8CurrentCommandState = 1;
                }
            }
            break;
        case 1:
            if (putDataAction()) {
                gstescposCommand.gu8CurrentCommandState = 2;
            }
            break;
        case 2:
            if (gstescposCommand.gu8Arg[0] == 0) {
                gstescposCommand.gu8CurrentCommandState = 0;
                return (1);
            }
            if (putFeedAction(gstescposCommand.gu8Arg[0] * getLineSpace())) {
                gstescposCommand.gu8CurrentCommandState = 0;
                return (1);
            }
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  select the current font
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_Character_Font(void) {
    /*wait for peek 1 Byte*/

    if (fifo_byte_Peek(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 0) == FIFO_ERR_NO_DAT) {
        return (0);
    }


    if (gstescposCommand.gu8Arg[0] == 0 || gstescposCommand.gu8Arg[0] == 48) {
        setCurrentFont(0);
        ReadCurrentCmd();
        return (1);
    }

    if (gstescposCommand.gu8Arg[0] == 1 || gstescposCommand.gu8Arg[0] == 49) {
        setCurrentFont(1);
        ReadCurrentCmd();
        return (1);

    }
    if (gstescposCommand.gu8Arg[0] == 2 || gstescposCommand.gu8Arg[0] == 50) {
        setCurrentFont(2);
        ReadCurrentCmd();
        return (1);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Printer rotate 90 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Pinter_Turn_90_Clockwise_Rotation_Mode(void) {
    /*wait for peek 1 Byte*/

    if (fifo_byte_Peek(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 0) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    if (gstescposCommand.gu8Arg[0] == 0 || gstescposCommand.gu8Arg[0] == 48) {
        setDrawingRotaion90(0);
        ReadCurrentCmd();
        return (1);
    }

    if (gstescposCommand.gu8Arg[0] == 1 || gstescposCommand.gu8Arg[0] == 49) {
        setDrawingRotaion90(1);
        ReadCurrentCmd();
        return (1);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : change size 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Set_Double_Width_And_Height(void) {
    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    setDrawingSizeX(((gstescposCommand.gu8Arg[0] >> 4) & 0x07) + 1);
    setDrawingSizeY((gstescposCommand.gu8Arg[0] & 0x07) + 1);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set justification value 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Select_Justification(void) {
    /*wait for peek 1 Byte*/

    if (PrintBufferHasData()) {
        return (1);
    }

    if (fifo_byte_Peek(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0], 0) == FIFO_ERR_NO_DAT) {
        return (0);
    }


    if (gstescposCommand.gu8Arg[0] == 0 || gstescposCommand.gu8Arg[0] == 48) {
        setJustification(0);
        ReadCurrentCmd();
        return (1);
    }

    if (gstescposCommand.gu8Arg[0] == 1 || gstescposCommand.gu8Arg[0] == 49) {
        setJustification(1);
        ReadCurrentCmd();
        return (1);
    }

    if (gstescposCommand.gu8Arg[0] == 2 || gstescposCommand.gu8Arg[0] == 50) {
        setJustification(2);
        ReadCurrentCmd();
        return (1);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set the setup down 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Turn_UpsideDown_Printing_Mode(void) {

    if (fifo_byte_Read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg) == FIFO_ERR_NO_DAT) {
        return (0);
    }
    SetupSideDown(gstescposCommand.gu8Arg[0]);
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Toggle_online_offline_mode(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Test_Page(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Line Space Command
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static uint8_t Printer_Set_Left_Blank_Margin_With_Dots(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set the  relative position 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Set_Relative_Print_Position(void) {
    /*wait for peek 2 Byte*/


    int16_t relative;
    if (fifo_bytes_read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 2) == FIFO_ERR_NO_DAT) {
        return (0);
    }

    relative = (gstescposCommand.gu8Arg[0] + (gstescposCommand.gu8Arg[1] << 8));
    setRelativeXPostion(relative);
    return (1);

}

__attribute__((unused)) static uint8_t Printer_Set_Printing_Area_Width(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Character Command
 ---------------------------------------------------------------------------------------------------
 */

__attribute__((unused)) static uint8_t Printer_Turn_White_Black_Printing_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Internation_Characters(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Character_Code_Table(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Chinese_Mode(void) {

    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Kanji Character Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static uint8_t Printer_Select_Character_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Print_Mode_Kanji_Characters(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Turn_Underline_Mode_Kanji(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Define_Kanji_Characters(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Set_Left_Right_Side_Kanji_Character(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Bit Image  Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused)) static uint8_t Printer_Define_Downloaded_BitImage(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Print_Downloaded_BitImage(void) {
    return (1);
}

__attribute__((unused)) static uint8_t Printer_Print_Bitmap(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : start Print NV-Image
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Print_NV_Bitmap(void) {
    if (gstescposCommand.gu8CurrentCommandState == 0) {
        if (BitNVImagesIsRead()) {
            return (1);
        }

        if (PrintBufferHasData()) {
            return (1);
        }
        if (fifo_bytes_peek(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 0, 2) == FIFO_ERR_NO_DAT) {
            return (0);
        }

        if (gstescposCommand.gu8Arg[0] == 0) {
            return (1);
        }

        if (loadCurrentIndex(gstescposCommand.gu8Arg[0], gstescposCommand.gu8Arg[1])) {
            fifo_bytes_remove(gpstEscPosReceiveBuffer, 2);
            gstescposCommand.gu8CurrentCommandState = 1;
        } else {
            return (1);
        }
    }

    if (gstescposCommand.gu8CurrentCommandState == 1) {
        if (PrintNvImage()) {
            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
        }
        return (0);
    }
    gstescposCommand.gu8CurrentCommandState = 0;
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set the setup down 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Define_NV_Bitmap(void) {

    if (gstescposCommand.gu8CurrentCommandState == 0) {

        if (BitNVImagesIsRead()) {
            return (1);
        }

        if (fifo_byte_Peek(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0], 0) == FIFO_ERR_NO_DAT) {
            return (0);
        }


        if (gstescposCommand.gu8Arg[0] == 0) {
            return (1);
        }

        if (setMaxLogo(gstescposCommand.gu8Arg[0]) == 0) {
            return (1);
        }
        /*remove arg from buffer*/
        (void) fifo_byte_remove(gpstEscPosReceiveBuffer);
        gstescposCommand.gu8CurrentCommandState = 1;
        return (0);
    }

    if (gstescposCommand.gu8CurrentCommandState == 1) {
        if (saveNvImage(gpstEscPosReceiveBuffer)) {
            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
        }
        return (0);
    }
    gstescposCommand.gu8CurrentCommandState = 0;
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Reset Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused)) static uint8_t Printer_Initialize(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Status Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static uint8_t Printer_Transmit_Status(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Generate_Pulse(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Enable_Disable_ASB(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Read_ID(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Process_ID(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   BarCode Commands  Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static uint8_t Printer_Select_Printing_Position_of_Human_Readable_Characters(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Barcode_Height(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Barcode_Width(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Font_For_HRI_Characters(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Print_Barcode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Barcode_Printing_Left_Space(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   controls parameter Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static uint8_t Printer_Select_Cancel_Panel_Button(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Cut_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Start_End_Macro_Definition(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Execute_Macro(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Beep_Tone(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : cut Operation
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 or 1 
 */
static uint8_t Printer_Cut_Paper(void) {

    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:
            if (fifo_byte_Peek(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0], 0) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            if (gstescposCommand.gu8Arg[0] == 1 || gstescposCommand.gu8Arg[0] == 49 || gstescposCommand.gu8Arg[0] == 48 || gstescposCommand.gu8Arg[0] == 0x00) {
                gstescposCommand.gu8CurrentCommandState = 1;
                ReadCurrentCmd();
                return (0);
            }
            if (gstescposCommand.gu8Arg[0] == 66) {
                ReadCurrentCmd();
                gstescposCommand.gu8CurrentCommandState = 2;
                return (0);
            }
            return (1);
            break;
        case 1:
            if (QueuLineEmpty()) {
                return (0);
            }
            CutNow();
            gstescposCommand.gu8CurrentCommandState = 3;
            break;
        case 2:
            if (fifo_byte_Read(gpstEscPosReceiveBuffer, &gstescposCommand.gu8Arg[0]) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            if (PrintBufferHasData()) {
                gstescposCommand.gu8CurrentCommandState = 4;
            } else {
                gstescposCommand.gu8CurrentCommandState = 5;
            }
            break;
        case 3:
            if (getCutState()) {
                gstescposCommand.gu8CurrentCommandState = 0;
                return (1);
            }
            break;
        case 4:
            if (putDataAction()) {
                gstescposCommand.gu8CurrentCommandState = 5;
            }
            break;
        case 5:
            if (putFeedAction(gstescposCommand.gu8Arg[0])) {
                gstescposCommand.gu8CurrentCommandState = 1;
            }
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
            break;
    }
    return (0);
}

__attribute__((unused))static uint8_t Printer_Select_Chinese_Code_Format(void) {
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :   Page Mode Commands
 ---------------------------------------------------------------------------------------------------
 */
__attribute__((unused))static void Printer_Print_And_Return_To_Standard_Mode_In_Page_mode(void) {
    return;
}

__attribute__((unused))static uint8_t Printer_Print_Data_In_mode_Page(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Page_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Standard_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Print_Direction_Page_mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Printing_Area_Page_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Print_2D_Barcode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Turn_Quadruple_Size_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Feed_Marked_Paper_To_Print_Starting_Position(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Absolute_Vertical_Print_Position_Page_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Execute_Test_Print(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Counter_Print_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Count_Mode_A(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_Count_Mode_B(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Counter(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Select_2D_Barcode_Type(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Relative_Vertical_Print_Position_Page_Mode(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Print_Counter(void) {
    return (1);
}

__attribute__((unused))static uint8_t Printer_Set_Horizontal_Vertical_Motion_Unit(void) {
    return (1);
}

static uint8_t PrinterMemTest(void) {
#if MEM_MODE_ACTIVE_COMANDS
    uint32_t address;
    if (flash_ready() == 0) {
        return (0);
    }
    switch (gstescposCommand.gu8CurrentCommandState) {
        case 0:

            if (fifo_bytes_read(gpstEscPosReceiveBuffer, gstescposCommand.gu8Arg, 5) == FIFO_ERR_NO_DAT) {
                return (0);
            }
            if (gstescposCommand.gu8Arg[0] == 0) {
                gstescposCommand.gu8CurrentCommandState = 2; /*write Page From memory*/
            } else if (gstescposCommand.gu8Arg[0] == 1) {
                gstescposCommand.gu8CurrentCommandState = 1; /*Read Page From memory*/
            } else if (gstescposCommand.gu8Arg[0] == 2) {
                gstescposCommand.gu8CurrentCommandState = 3; /*Read Page From memory*/
            } else {
                return (1);
            }
            break;
        case 1:
            address = (uint32_t) ((gstescposCommand.gu8Arg[1] << 16) | (gstescposCommand.gu8Arg[2] << 8) | (gstescposCommand.gu8Arg[3]));
            flash_read_data(gu8memPage, address, 4512U);
            gstescposCommand.gu8CurrentCommandState = 4;
            break;
        case 2:

            setBuff(gu8memPage, gstescposCommand.gu8Arg[4], 4512U);
            address = (uint32_t) ((gstescposCommand.gu8Arg[1] << 16) | (gstescposCommand.gu8Arg[2] << 8) | (gstescposCommand.gu8Arg[3]));
            flash_write_data(gu8memPage, address, 4512U);
            gstescposCommand.gu8CurrentCommandState = 4;
            break;
        case 3:
            flash_chip_erase();
            gstescposCommand.gu8CurrentCommandState = 4;
            break;
        case 4:
            if (flash_error()) {
                gstescposCommand.gu8CurrentCommandState = 0;
                run_flash_error();
                return (1);
            }
            if (gstescposCommand.gu8Arg[0] == 0x01) {
                for (uint16_t i = 0; i < 4512; i++) {
                    printHex(gu8memPage[i]);
                }
                PrintCmd(0x0A);
                PrintCmd(0x0A);
                PrintCmd(0x0A);
            } else {
                setNumberOfTone(2);
            }

            gstescposCommand.gu8CurrentCommandState = 0;
            return (1);
            break;
        default:
            gstescposCommand.gu8CurrentCommandState = 0;
            break;
    }
    return (0);
#else
    return (1);
#endif
}

static uint8_t PrinterDefaultCMD(void) {
    return (1);
}
