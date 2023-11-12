
#include <font.h>
#include <sys/_stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gd32f30x_gpio.h>
#include <system.h>
#include <stdint-gcc.h>
#include "escpos.h"
#include "userDefineCharAndBitImag.h"
#include "fifo.h"
#include "utility.h"
#include "standmode.h"

#define DEPUG_LINE                 (1)


#define  DEFAULT_MARIGN      64
#define  MAX_BYTE_PER_CHAR    36
#define  CODE_PAGE_LENGHT    128U*MAX_BYTE_PER_CHAR
#define  MAX_DOT_DATA_Y         192
#define  MAX_DOT_DATA_X         576


#define MAX_PRINT_BUFFER_IMAGE      (MAX_DOT_DATA_Y * (MAX_DOT_DATA_X>>3))
#define MEMORY_LOGS_ADDRESS             0x1C0000U
#define MEMEORY_LOGD_END_ADDRESS        0x1FFFFFU
#define HERADER_END_ADDRESS              MEMORY_LOGS_ADDRESS-1U
#define HERADER_LOGOS_ADDRESS           (HERADER_END_ADDRESS)-(MAX_LOGO*(sizeof(BitImageHeader_t)))
#define NV_IMAGES_START_ADDRESS            HERADER_LOGOS_ADDRESS

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &=  ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))



#define  MAX(X , Y)                    (X>=Y)?(X):(Y)
#define DEFAULT_LINE_SPACE             30  //3.75 mm  (30*0.125mm)
#define PIXEL_SIZEum                  125


ut_dip_switch_t gutDipSwitch;

typedef struct {
    uint32_t MaxSize;
    uint16_t u16ReminderBuffers;
    uint16_t u16NumberBuffer;
    uint8_t u8LoadHeadersVar;
    uint8_t u8ImageStateVar;
    uint8_t u8HeaderIndex;
    uint8_t u8MaxLog;
} st_images_mang_t;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Save Y
 ---------------------------------------------------------------------------------------------------
 */

typedef struct {
    uint8_t *BitImageData;
    uint8_t m;
    uint8_t Flag;
    uint16_t width;
} stBitImageData;

typedef struct {
    uint8_t u8TabIndex;
    uint8_t u8MaxTab;
    uint8_t u8WriteCharState;
    uint8_t u8WriteIndex;
    uint8_t u8ReadIndex;
} st_var_t;




static uint8_t gu8DrawBuffer[72 * 192];



/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : current logo data
 ---------------------------------------------------------------------------------------------------
 */
static BitImageHeader_t gstBitImageHeader;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : main global variables
 ---------------------------------------------------------------------------------------------------
 */
static st_images_mang_t gstImagesMangement;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Drawing struct
 ---------------------------------------------------------------------------------------------------
 */
static st_drawing_t gstDrawing;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Drawing struct
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t gu8TabTabl[MAX_TAB_IN_LINE];
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Buffer
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t gu8CodePageBitMap[CODE_PAGE_LENGHT]; /*Bit Map Of Code Page*/

static uint8_t gu8CurrentCharsBitmap[36];
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Save Y
 ---------------------------------------------------------------------------------------------------
 */
static st_var_t gstVar;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Save Y
 ---------------------------------------------------------------------------------------------------
 */
static stBitImageData gstBitImag;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Internal Functions
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t ReverseBits(uint8_t Byte);
static void drawBitImage(uint16_t x, uint16_t y, uint8_t nRow, uint16_t width, uint8_t *BitMap, uint8_t density);
static void DrawImagBitWithInChar();


static uint8_t DefineNvBitImage(uint8_t index, uint16_t x, uint16_t y);



static inline uint8_t checkToPrintData(uint16_t w, uint16_t max);
static void GetBitmap(uint8_t c);
static void ModifiyBitMap();
static void DrawBitmapChars(uint16_t maxWidth, uint8_t RightSpace, uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap);
static void DrawBitmapImages(uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap);
static void DrawBitmapChars90(uint16_t maxWith, uint8_t RightSpace, uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Create Frame Buffer (Pixel Buffer)
 ---------------------------------------------------------------------------------------------------
 *  @param : max Pixel ber line 
 * 
 *  @param : max number of line 
 * 
 * 
 * @return:  none
 */
void PixelBufferInit(uint16_t maxPixel, uint16_t maxLine) {
    gstDrawing.u16MaxDotLine = maxPixel;
    gstDrawing.u16MaxLine = maxLine;
    gstDrawing.i16LeftMargin = (0); /*default is 0*/
    gstDrawing.u8CharRightSpace = 0;
    gstDrawing.u16LineSpace = DEFAULT_LINE_SPACE;
    gstDrawing.u16XPos = gstDrawing.i16LeftMargin;
    gstDrawing.u16YPos = gstDrawing.u16LineSpace;
    gstDrawing.characterSytel.characterSytel = 0U;
    gstDrawing.characterSytel.xSize = 1; /*up to 8*/
    gstDrawing.characterSytel.ySize = 1; /*up to 8*/
    setBuff(gu8CodePageBitMap, 0x00, CODE_PAGE_LENGHT);
    /*create current buffer with */
    gstVar.u8MaxTab = 0;
    gstVar.u8TabIndex = 0;
    gstVar.u8WriteCharState = 0;
    gstVar.u8TabIndex = 0;
    gstVar.u8WriteIndex = 0;
    gstVar.u8ReadIndex = 0;
    Default_Tab_set();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Font
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current Font select
 */
uint8_t getCurrentFont(void) {
    return (gstDrawing.characterSytel.Characterfont & 0x01);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size X
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDrawingSizeX(uint8_t x) {
    gstDrawing.characterSytel.xSize = x;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size X
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDrawingSizeY(uint8_t y) {
    gstDrawing.characterSytel.ySize = y;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set double strike
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDoubleStrike(uint8_t value) {
    gstDrawing.characterSytel.strike = value & 0x01;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size Y
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void SetupSideDown(uint8_t Value) {
    gstDrawing.characterSytel.upside_down = Value & 0x01;
}

uint8_t getupSizeDown() {
    return gstDrawing.characterSytel.upside_down;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set justification Value
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setJustification(uint8_t Value) {
    gstDrawing.characterSytel.justification = Value & 0x03;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set up Side Down
 ---------------------------------------------------------------------------------------------------
 *  @param : code page number 
 * 
 * @return:  void
 */
void setDrawingCPSet(uint8_t cpSet) {
    gstDrawing.characterSytel.CodePageSelect = cpSet & 0x7F;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set rotation setting for display
 ---------------------------------------------------------------------------------------------------
 *  @param : 0 thru 3 corresponding to 4 cardinal rotations
 * 
 * @return:  current with
 */
void setDrawingRotaion90(uint8_t Enable) {
    gstDrawing.characterSytel.rotate90 = Enable & 0x01;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set default line space
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current with
 */
void setDefaultLineSpace(void) {
    gstDrawing.u16LineSpace = DEFAULT_LINE_SPACE;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set rotation setting for display
 ---------------------------------------------------------------------------------------------------
 *  @param : set line space value
 * 
 * @return:  current with
 */
void setLineSpace(uint16_t vaule_per_dot) {
    gstDrawing.u16LineSpace = vaule_per_dot;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Font
 ---------------------------------------------------------------------------------------------------
 *  @param : Current Font Select
 * 
 * @return:  current with
 */
void setCurrentFont(uint8_t Font) {
    gstDrawing.characterSytel.Characterfont = Font & 0x03;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current under Line
 ---------------------------------------------------------------------------------------------------
 *  @param : number of dot to under line Data
 * 
 * @return:  current with
 */
void setCurrentUnderLine(uint8_t nDon) {
    gstDrawing.characterSytel.underLine = nDon & 0x01;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Bold
 ---------------------------------------------------------------------------------------------------
 *  @param : Current Char is bold Select
 * 
 * @return:  current with
 */
void setCurrentBold(uint8_t bold) {
    gstDrawing.characterSytel.blod = bold & 0x01;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current x position 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current y position
 */
uint16_t getLineSpace() {
    return (gstDrawing.u16LineSpace);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get max number of dot per line 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: max number of dot per line 
 */
uint16_t getMaxDotPerLine() {
    return (gstDrawing.u16MaxDotLine);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : change current fonts 
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to current stander fonts
 * 
 * @return : none
 */
void assignemtNewFont(st_standFont_t *standFont) {
    gstDrawing.pstandFont = (st_standFont_t *) standFont;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Current Data is bold or not
 ---------------------------------------------------------------------------------------------------
 * @param : Blod state flag 0: is normal 1:is bold
 */
void drawCharActiveBlodState(uint8_t En) {

    gstDrawing.characterSytel.blod = En & 0x01;
}

void WriteChar(uint8_t Char) {
#if TESET_TIME
    uint32_t Time = systemMacros();
#endif


    if (gstBitImag.Flag) {
        gstBitImag.Flag = 0;
        DrawImagBitWithInChar();
    }
    GetBitmap(Char);
    ModifiyBitMap();
    if (gstDrawing.characterSytel.rotate90) {
        DrawBitmapChars90(gstDrawing.u16MaxDotLine, gstDrawing.u8CharRightSpace, gstDrawing.pstandFont->w, gstDrawing.pstandFont->h, gstDrawing.characterSytel.xSize, gstDrawing.characterSytel.ySize, gu8CurrentCharsBitmap);
    } else {
        DrawBitmapChars(gstDrawing.u16MaxDotLine, gstDrawing.u8CharRightSpace, gstDrawing.pstandFont->w, gstDrawing.pstandFont->h, gstDrawing.characterSytel.xSize, gstDrawing.characterSytel.ySize, gu8CurrentCharsBitmap);
    }
#if TESET_TIME
    Time = systemMacros() - Time;
    if (Time < minTime) {
        minTime = Time;
    }
    if (Time >= maxTime) {
        maxTime = Time;
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  reverse byte
 ---------------------------------------------------------------------------------------------------
 * @param : byte to be reverse
 * 
 * 
 * @return:none
 */
static uint8_t ReverseBits(uint8_t Byte) {
    uint8_t reverseByte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (bitRead(Byte, i)) {

            reverseByte |= (0x80 >> i);
        }
    }
    return reverseByte;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set space between char
 ---------------------------------------------------------------------------------------------------
 * @param : number of dot
 * 
 * @return:none
 */
void setSpaceBetweenChar(uint8_t n) {
    if (gstDrawing.characterSytel.xSize > 1) {
        n <<= 1;
    }
    gstDrawing.u8CharRightSpace = n;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Left Margin of the Printer
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void setLeftMargin(int16_t leftMargin) {
    if (leftMargin >= gstDrawing.u16MaxDotLine) {
        return;
    }
    gstDrawing.i16LeftMargin = leftMargin;
    gstDrawing.u16XPos = leftMargin;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void WriteBitImage(uint8_t m, uint16_t width, stByteFIFO_t *BitImage) {
    uint8_t reverseByte;
    uint8_t maxRow;
    uint8_t CurrentByte;
    uint8_t BitWidth;
    maxRow = 1;
    BitWidth = 0;
    if (m == 32 || m == 33) {
        maxRow = 3;
    }

    if (m == 0 || m == 32) {
        BitWidth = 1;
    }




    gstBitImag.BitImageData = (uint8_t *) malloc(maxRow * width);
    if (gstBitImag.BitImageData == NULL) {
        return;
    }



    /*convert operation*/
    /*
     * d0   d3  d6    d09   ==   d2    d5  d8   d11   with reverse each byte bits
     * d1   d4  d7    d10   ==   d1    d4  d7   d10   with reverse each byte bits
     * d2   d5  d8    d11   ==   d0    d3  d6   d09  with reverse each byte bits
     */

    for (uint16_t col = 0; col < (width); col++) {
        for (uint8_t Row = 0; Row < maxRow; Row++) {
            CurrentByte = BitImage->pByteBuffer[((maxRow - 1) - Row) + (col * maxRow)];
            reverseByte = ReverseBits(CurrentByte);
            gstBitImag.BitImageData[Row + (col * maxRow)] = reverseByte;
        }
    }

    (void) fifo_bytes_remove(BitImage, width * maxRow);

    gstBitImag.Flag = 0;
    gstBitImag.m = m;
    gstBitImag.width = width;
    if (checkToPrintData((width << BitWidth), gstDrawing.u16MaxDotLine)) {
        return;
    }
    DrawImagBitWithInChar();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  draw bitmap Image
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
static void drawBitImage(uint16_t x, uint16_t y, uint8_t nRow, uint16_t width, uint8_t *BitMap, uint8_t density) {

    uint8_t BitWitdth;


    BitWitdth = density + 1;
    if (gstDrawing.characterSytel.rotate90) {
        DrawBitmapChars90(gstDrawing.u16MaxDotLine, gstDrawing.u8CharRightSpace, BitWitdth*width, nRow, 1, 1, BitMap);
    } else {
        DrawBitmapChars(gstDrawing.u16MaxDotLine, gstDrawing.u8CharRightSpace, BitWitdth*width, nRow, 1, 1, BitMap);
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  draw bitmap Image
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
static void DrawImagBitWithInChar() {
    if (gstBitImag.m == 1) {
        drawBitImage(gstDrawing.u16XPos, gstDrawing.u16YPos, 8, gstBitImag.width, gstBitImag.BitImageData, 0);
        gstDrawing.u16XPos += gstBitImag.width;
    } else if (gstBitImag.m == 32) {
        drawBitImage(gstDrawing.u16XPos, gstDrawing.u16YPos, 24, gstBitImag.width, gstBitImag.BitImageData, 1);
        gstDrawing.u16XPos += gstBitImag.width << 1;
    } else if (gstBitImag.m == 33) {
        drawBitImage(gstDrawing.u16XPos, gstDrawing.u16YPos, 24, gstBitImag.width, gstBitImag.BitImageData, 0);
        gstDrawing.u16XPos += gstBitImag.width;
    } else {
        drawBitImage(gstDrawing.u16XPos, gstDrawing.u16YPos, 8, gstBitImag.width, gstBitImag.BitImageData, 1);
        gstDrawing.u16XPos += gstBitImag.width << 1;
    }
    //Free the Bit Image data
    gstDrawing.u16YPos = MAX(gstDrawing.u16YPos, 24);
    free(gstBitImag.BitImageData);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Fill the Tab Option
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
uint8_t fillTabBuffer(uint8_t value, uint8_t Index) {
    if (Index >= MAX_TAB_IN_LINE) {
        return (0);
    }
    if (value > MAX_TAB_IN_LINE) {
        return (0);
    }
    gu8TabTabl[Index] = value;
    gstVar.u8MaxTab = Index + 1;
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set Tab Process
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void TabPorcess() {
    uint8_t CurrentTab;
    uint16_t TabWidth;
    uint8_t Max;


    if (gstVar.u8MaxTab == 0) {
        /*work as Default Tab*/
        CurrentTab = 8 + (gstVar.u8TabIndex << 3);
        Max = MAX_TAB_IN_LINE;
    } else {
        CurrentTab = gu8TabTabl[gstVar.u8TabIndex];
        Max = gstVar.u8MaxTab;
    }

    if (CurrentTab == 0) {
        return;
    }

    TabWidth = CurrentTab * ((gstDrawing.pstandFont->w * gstDrawing.characterSytel.xSize) + gstDrawing.u8CharRightSpace);
    if (gstDrawing.u16XPos > TabWidth - 1) {
        gstVar.u8TabIndex = 0;
        return;
    }
    gstDrawing.u16XPos = TabWidth + gstDrawing.i16LeftMargin;
    gstVar.u8TabIndex = (gstVar.u8TabIndex + 1) % Max;

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set Tab to default values
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void Default_Tab_set() {
    gstVar.u8TabIndex = 0;
    gstVar.u8MaxTab = 0;
    for (uint8_t i = 0; i < MAX_TAB_IN_LINE; i++) {
        gu8TabTabl[i] = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : check to Print width
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
static inline uint8_t checkToPrintData(uint16_t w, uint16_t max) {
    if ((gstDrawing.u16XPos + (w)) > max) {
        gstVar.u8TabIndex = 0;
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get The Current Hight
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * 
 * @return:value of max Hight
 */
uint8_t PrintBufferHasData() {
    if (gstDrawing.u16XPos > gstDrawing.i16LeftMargin) {
        return (1);
    }
    return (0);
}

/*
---------------------------------------------------------------------------------------------------
 * @brief : set Absolute x postion
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  void
 */
void setAbsoluteXPostion(uint16_t xpos) {
    gstDrawing.u16XPos = xpos + gstDrawing.i16LeftMargin;
}

/*
---------------------------------------------------------------------------------------------------
 * @brief : set Relative x postion
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  void
 */
void setRelativeXPostion(uint16_t xpos) {

    gstDrawing.u16XPos += xpos;
}

/*
---------------------------------------------------------------------------------------------------
 * @brief : return last Ypos
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  Ypos
 */
uint16_t getLastDataYpos() {

    return (gstDrawing.u16YPos);
}

/*
---------------------------------------------------------------------------------------------------
 * @brief : put Feed Action
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 or one 
 */
uint8_t putFeedAction(uint16_t nFeed) {
    if (PutAction(nFeed, gu8DrawBuffer, 0, 0, 0)) {
        return (1);
    }
    return (0);
}

/*
---------------------------------------------------------------------------------------------------
 * @brief : put action 
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 or one 
 */
uint8_t putDataAction() {
    if (PutAction(gstDrawing.u16YPos, gu8DrawBuffer, gstDrawing.u16XPos, gstDrawing.characterSytel.justification, 1)) {
        gstDrawing.u16XPos = gstDrawing.i16LeftMargin;
        gstDrawing.u16YPos = gstDrawing.u16LineSpace;
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Get max line in buffer
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : max dot line
 *
 */
uint16_t getMaxLine() {
    return gstDrawing.u16MaxLine;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init all variables in this buffer
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
void ImagesInit() {
    gstImagesMangement.MaxSize = 0;
    setBuff(&gstBitImageHeader, 0x00, sizeof (BitImageHeader_t));
    gstImagesMangement.u8ImageStateVar = 0;
    gstImagesMangement.u8HeaderIndex = 0;
    gstImagesMangement.u16ReminderBuffers = 0;
    gstImagesMangement. u16NumberBuffer = 0;
    gstImagesMangement.u8LoadHeadersVar = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : save data into memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
uint8_t saveNvImage(stByteFIFO_t *pReceiveBuffer) {

    uint16_t x;
    uint16_t y;
    if (flash_ready() == 0) {
        return (0);
    }
    switch (gstImagesMangement.u8ImageStateVar) {
        case 0:
            if (gstImagesMangement.u8HeaderIndex < gstImagesMangement.u8MaxLog) {
                /*wait for 4Byte*/
                if (fifo_bytes_read(pReceiveBuffer, gutUserBuffer.st_BitImage_t.defineImageBuffer, 4) == FIFO_ERR_NO_DAT) {
                    return (0);
                }
                x = gutUserBuffer.st_BitImage_t.defineImageBuffer[0] + (gutUserBuffer.st_BitImage_t.defineImageBuffer[1] << 8);
                y = gutUserBuffer.st_BitImage_t.defineImageBuffer[2] + (gutUserBuffer.st_BitImage_t.defineImageBuffer[3] << 8);
                if (DefineNvBitImage((gstImagesMangement.u8HeaderIndex + 1), x, y)) {
                    gstImagesMangement.u8ImageStateVar = 1;
                } else {
                    gstImagesMangement.u8ImageStateVar = 9;
                }
                return (0);
            }
            gstImagesMangement.MaxSize = 0;
            gstImagesMangement.u8MaxLog = 0;
            gstImagesMangement.u8HeaderIndex = 0;
            gstImagesMangement.u8ImageStateVar = 7;
            break;
        case 1:
            /*wait for */
            if (gstImagesMangement.u16NumberBuffer > 0) {
                if (fifo_bytes_read(pReceiveBuffer, gutUserBuffer.st_BitImage_t.defineImageBuffer, MAX_BUFFER) == FIFO_ERR_NO_DAT) {
                    return (0);
                }
                gstImagesMangement.u8ImageStateVar = 2;
                return (0);
            }

            if (gstImagesMangement.u16ReminderBuffers > 0) {
                if (fifo_bytes_read(pReceiveBuffer, gutUserBuffer.st_BitImage_t.defineImageBuffer, gstImagesMangement. u16ReminderBuffers) == FIFO_ERR_NO_DAT) {
                    return (0);
                }
                gstImagesMangement.u8ImageStateVar = 4;
                return (0);
            }
            gstImagesMangement.u8ImageStateVar = 6;
            break;
        case 2:
            flash_write_data((uint8_t *) gutUserBuffer.st_BitImage_t.defineImageBuffer, gstBitImageHeader.u32Address, MAX_BUFFER);
            gstImagesMangement.u8ImageStateVar = 3;
            break;
        case 3:
            gstImagesMangement.u8ImageStateVar = 1;
            if (flash_error()) {
                run_flash_error();
                return (1);
            }
            gstImagesMangement.u16NumberBuffer--;
            gstBitImageHeader.u32Address += MAX_BUFFER;

            break;
        case 4:
            flash_write_data((uint8_t *) gutUserBuffer.st_BitImage_t.defineImageBuffer, gstBitImageHeader.u32Address, gstImagesMangement.u16ReminderBuffers);
            gstImagesMangement.u8ImageStateVar = 5;
            break;
        case 5:
            if (flash_error()) {
                run_flash_error();
                return (1);
            }
            gstBitImageHeader.u32Address += gstImagesMangement.u16ReminderBuffers;
            gstImagesMangement. u8ImageStateVar = 1;
            gstImagesMangement.u16ReminderBuffers = 0;
            break;
        case 6:
            gutUserBuffer.st_BitImage_t.header[gstImagesMangement.u8HeaderIndex].Size.Index = gstBitImageHeader.Size.Index;
            gutUserBuffer.st_BitImage_t.header[gstImagesMangement.u8HeaderIndex].Size.size = gstBitImageHeader.Size.size;
            gutUserBuffer.st_BitImage_t.header[gstImagesMangement.u8HeaderIndex].h = gstBitImageHeader.h;
            gutUserBuffer.st_BitImage_t.header[gstImagesMangement.u8HeaderIndex].w = gstBitImageHeader.w;
            gstImagesMangement.u8HeaderIndex++; /*Increment*/
            gutUserBuffer.st_BitImage_t.header[gstImagesMangement.u8HeaderIndex].u32Address = gstBitImageHeader.u32Address;
            gstImagesMangement.u8ImageStateVar = 0;
            break;
        case 7:
            flash_write_data((uint8_t *) gutUserBuffer.st_BitImage_t.header, HERADER_LOGOS_ADDRESS, sizeof (BitImageHeader_t) * MAX_LOGO);
            gstImagesMangement.u8ImageStateVar = 8;
        case 8:
            gstImagesMangement.u8ImageStateVar = 0;
            if (flash_error()) {
                run_flash_error();
                return (1);
            }
            return (1);
            break;
        case 9: /*Dump-State*/
            if (gstImagesMangement.u16NumberBuffer > 0) {
                if (fifo_bytes_read(pReceiveBuffer, gutUserBuffer.st_BitImage_t.defineImageBuffer, MAX_BUFFER) == FIFO_ERR_NO_DAT) {
                    return (0);
                }
                gstImagesMangement.u16NumberBuffer--;
                return (0);
            }

            if (gstImagesMangement.u16ReminderBuffers > 0) {
                if (fifo_bytes_read(pReceiveBuffer, gutUserBuffer.st_BitImage_t.defineImageBuffer, gstImagesMangement. u16ReminderBuffers) == FIFO_ERR_NO_DAT) {
                    return (0);
                }
                gstImagesMangement.u16ReminderBuffers = 0;
            }
            gstImagesMangement.u8ImageStateVar = 0;
            gstImagesMangement.u8HeaderIndex++; /*Increment*/
            break;
        default:
            gstImagesMangement.u8ImageStateVar = 0;
            run_flash_error();
            return (1);
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Define bit images
 ---------------------------------------------------------------------------------------------------
 * @param :index of the bit images {1-57}
 * 
 * @parm : max byte in x
 * 
 * @return : max byte in y
 */
static uint8_t DefineNvBitImage(uint8_t index, uint16_t x, uint16_t y) {

    uint32_t size;
    gstBitImageHeader.h = y << 3; /*12*8 = 96 byte*/
    gstBitImageHeader.w = x << 3; /*48*8 =384 dot */
    gstBitImageHeader.Size.Index = index;
    size = (x * y) << 3; /*12*48*8 = 4609byte*/
    gstImagesMangement.u16ReminderBuffers = size % MAX_BUFFER;
    gstImagesMangement.u16NumberBuffer = size / MAX_BUFFER;
    gstImagesMangement.MaxSize += size;
    if (gstImagesMangement.MaxSize >= (256U * 1024U)) {
        return (0);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  :Load Headers
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @parm : max lines prints
 * 
 * @return : none
 */
uint8_t upLoadHeaders() {

    if (flash_ready() == 0) {
        return (0);
    }
    switch (gstImagesMangement.u8LoadHeadersVar) {
        case 0:
            flash_read_data((uint8_t *) gutUserBuffer.st_BitImage_t.header, HERADER_LOGOS_ADDRESS, MAX_LOGO * (sizeof (BitImageHeader_t)));
            gstImagesMangement.u8LoadHeadersVar = 1;
            break;
        case 1:
            if (flash_error()) {
                gstImagesMangement.u8LoadHeadersVar = 0;
                run_flash_error();
                return (1);
            }

            if (gutUserBuffer.st_BitImage_t.header[0].Size.Index == 0xFF) {
                for (uint16_t i = 0; i < MAX_LOGO; i++) {
                    setBuff((uint8_t *) gutUserBuffer.st_BitImage_t.header, 0x00, MAX_LOGO * (sizeof (BitImageHeader_t)));
                }
                gstImagesMangement.u8LoadHeadersVar = 2;
            } else {
                gstImagesMangement.u8LoadHeadersVar = 0;
                return (1);
            }
            break;
        case 2:
            flash_write_data((uint8_t *) gutUserBuffer.st_BitImage_t.header, HERADER_LOGOS_ADDRESS, MAX_LOGO * sizeof (BitImageHeader_t));
            gstImagesMangement.u8LoadHeadersVar = 3;
            break;
        case 3:
            gstImagesMangement.u8LoadHeadersVar = 0;
            if (flash_error()) {
                run_flash_error();
            }
            return (1);
            break;
        default:
            gstImagesMangement.u8LoadHeadersVar = 0;
            return (1);
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  :Bit Nv Images is Ready
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @parm : none
 * 
 * @return : none
 */
uint8_t BitNVImagesIsRead() {
    return gstImagesMangement.u8LoadHeadersVar;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  :save max logo
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @parm : none
 * 
 * @return : none
 */
uint8_t setMaxLogo(uint8_t MaxLog) {
    if (MaxLog > MAX_LOGO) {
        return (0);
    }
    /*Reset header buffer*/
    setBuff(gutUserBuffer.st_BitImage_t.header, 0x00, sizeof (BitImageHeader_t) * MAX_LOGO);
    gstImagesMangement.u8ImageStateVar = 0;
    gstImagesMangement.u8MaxLog = MaxLog;
    gstImagesMangement.u8HeaderIndex = 0;
    gutUserBuffer.st_BitImage_t.header[0].u32Address = MEMORY_LOGS_ADDRESS;
    gstBitImageHeader.u32Address = MEMORY_LOGS_ADDRESS;
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : load current Index From memory
 ---------------------------------------------------------------------------------------------------
 * @param :index 
 * 
 * @parm : m Density
 * 
 * @return : 0 is not found , 1 is found
 */
uint8_t loadCurrentIndex(uint8_t index, uint8_t m) {
    if (index == 0) {
        return (0);
    }
    /*serach and set data */

    for (uint8_t i = 0; i < MAX_LOGO; i++) {
        if ((gutUserBuffer.st_BitImage_t.header[i].Size.Index == index)) {
            copyBuff(&gstBitImageHeader, &gutUserBuffer.st_BitImage_t.header[i], sizeof (BitImageHeader_t));
            if (gstBitImageHeader.h == 0 || gstBitImageHeader.w == 0) {
                return (0);
            }
            if ((gstBitImageHeader.w * gstBitImageHeader.Size.Xsize) >= gstDrawing.u16MaxDotLine) {
                return (0);
            }

            gstImagesMangement.u16ReminderBuffers = (gstBitImageHeader.h) % 24;
            gstImagesMangement.u16NumberBuffer = (gstBitImageHeader.h) / 24;


            if (m == 1 || m == 49) {
                gstBitImageHeader.Size.Xsize = 2;
                gstBitImageHeader.Size.Ysize = 1;
                return (1);
            }
            if (m == 2 || m == 50) {
                gstBitImageHeader.Size.Xsize = 1;
                gstBitImageHeader.Size.Ysize = 2;
                return (1);
            }
            if (m == 3 || m == 51) {
                gstBitImageHeader.Size.Xsize = 2;
                gstBitImageHeader.Size.Ysize = 2;
                return (1);
            }
            gstBitImageHeader.Size.Xsize = 1;
            gstBitImageHeader.Size.Ysize = 1;

            return (1);
        }
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
uint8_t PrintNvImage() {

    uint8_t nBytePerRead;
    uint16_t x = 0;
    uint16_t ByteHight;
    uint8_t readData[24 * 72];

    if (gstImagesMangement.u8ImageStateVar) {
        if (putDataAction()) {
            gstImagesMangement.u8ImageStateVar = 0;
        }
        return (0);
    }



    if (gstImagesMangement.u16NumberBuffer > 0) {
        nBytePerRead = (24 >> 3);
        x = 0;
        ByteHight = ((gstBitImageHeader.h + 7) >> 3);
        while (x < gstBitImageHeader.w) {
            flash_read_data(readData + (x * nBytePerRead), gstBitImageHeader.u32Address + (x * ByteHight), nBytePerRead);
            while (flash_ready() == 0);
            x++;
        }

        /*swap to Pointer*/
        DrawBitmapImages(gstBitImageHeader.w, 24, gstBitImageHeader.Size.Xsize, gstBitImageHeader.Size.Ysize, readData);
        gstImagesMangement.u8ImageStateVar = 1;
        gstImagesMangement.u16NumberBuffer--;
        gstBitImageHeader.u32Address += 3;
        return (0);
    }

    if (gstImagesMangement.u16ReminderBuffers > 0) {
        x = 0;
        nBytePerRead = ((gstImagesMangement.u16ReminderBuffers + 7) >> 3);
        ByteHight = ((gstBitImageHeader.h + 7) >> 3);

        while (x < gstBitImageHeader.w) {
            flash_read_data(readData + (x * nBytePerRead), gstBitImageHeader.u32Address + (x * ByteHight), nBytePerRead);
            while (flash_ready() == 0);
            x++;
        }
        /*swap to Pointer*/
        DrawBitmapImages(gstBitImageHeader.w, gstImagesMangement.u16ReminderBuffers, gstBitImageHeader.Size.Xsize, gstBitImageHeader.Size.Ysize, readData);
        gstImagesMangement.u8ImageStateVar = 1;
        gstImagesMangement.u16ReminderBuffers = 0;
        return (0);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
static void DrawBitmapChars(uint16_t maxWidth, uint8_t RightSpace, uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap) {
    uint16_t width = (xSize * w);
    uint16_t maxLineWidth = gstDrawing.u16XPos + (width);
    gstVar.u8TabIndex = 0;
    if ((maxLineWidth + RightSpace) > maxWidth) {
        (void) putDataAction();
        return;
    }


    uint16_t y2 = 0;
    uint16_t x2 = 0;


    uint16_t color = 0;
    uint16_t mask = 0;
    uint16_t byteIndex = 0;
    uint16_t rowIndex = 0;
    uint16_t startY = gstDrawing.u16MaxLine - (h * ySize);

    uint16_t nByteBitmap = ((h + 7) >> 3);
    uint16_t row_bytes = ((gstDrawing.u16MaxDotLine + 7) >> 3);
    for (uint16_t j = startY; j < gstDrawing.u16MaxLine; j++) {
        uint16_t dividY = (y2 / ySize);
        mask = (0x01 << (dividY & 7));
        byteIndex = (dividY >> 3);
        rowIndex = j*row_bytes;
        x2 = 0;
        for (uint16_t i = gstDrawing.u16XPos; i < maxLineWidth; i++) {
            color = (bitmap[((x2 / xSize) * (nByteBitmap) + byteIndex)]) & mask;
            if (color) {
                gu8DrawBuffer[(i >> 3) + (rowIndex)] |= (0x80 >> (i & 7));
            }
            x2++;
        }
        y2++;
    }

    gstDrawing.u16XPos += (width);
    gstDrawing.u16YPos = MAX(gstDrawing.u16YPos, h * ySize);
    ReadCurrentCmd();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
static void DrawBitmapImages(uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap) {

    uint16_t width = w * xSize;
    uint16_t maxLineWidth = gstDrawing.u16XPos + (width);
    uint16_t y2 = 0;
    uint16_t x2 = 0;
    uint16_t color = 0;
    uint16_t mask = 0;
    uint16_t byteIndex = 0;
    uint16_t rowIndex = 0;
    uint16_t startY = gstDrawing.u16MaxLine - (h * ySize);
    uint16_t nByteBitmap = ((h + 7) >> 3);
    uint16_t row_bytes = ((gstDrawing.u16MaxDotLine + 7) >> 3);
    for (uint16_t j = startY; j < gstDrawing.u16MaxLine; j++) {
        uint16_t dividY = (y2 / ySize);
        mask = (0x80 >> (dividY & 7));
        byteIndex = (dividY >> 3);
        rowIndex = j*row_bytes;
        x2 = 0;
        for (uint16_t i = gstDrawing.u16XPos; i < maxLineWidth; i++) {
            color = (bitmap[((x2 / xSize) * (nByteBitmap) + byteIndex)]) & mask;
            if (color) {
                gu8DrawBuffer[(i >> 3) + (rowIndex)] |= (0x80 >> (i & 7));
            }
            x2++;
        }
        y2++;
    }
    gstDrawing.u16XPos = width;
    gstDrawing.u16YPos = (h * ySize);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
static void GetBitmap(uint8_t c) {

    uint8_t FirstChar;

    if (getStateOFuserDefine(c) == 0) {
        gstDrawing.pstandFont = getCurrentstandFont(gstDrawing.characterSytel.Characterfont);
        if (c >= 0x20 && c < 0x80) {
            FirstChar = 0x20;
        } else {
            gstDrawing.pstandFont->pu8Bitmap = (uint8_t *) gu8CodePageBitMap;
            FirstChar = 0x80;
        }
    } else {
        /*set current */
        getFontWithBitmap(c, gstDrawing.pstandFont);
        FirstChar = getUserDefineCharFirstChar();

    }
    /*chack*/
    uint8_t *bitmap = &gstDrawing.pstandFont->pu8Bitmap[(c - FirstChar) * gstDrawing.pstandFont->NBytePerChar]; /*first byte*/
    copyBuff(gu8CurrentCharsBitmap, bitmap, gstDrawing.pstandFont->NBytePerChar);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
static void ModifiyBitMap() {


    if (gstDrawing.characterSytel.underLine) {
        uint8_t maxByte = ((gstDrawing.pstandFont->h + 7)) >> 3;
        for (uint8_t i = 0; i < gstDrawing.pstandFont->w; i++) {
            gu8CurrentCharsBitmap[2 + (i * maxByte)] |= 0x40;
        }
    }

    if (gstDrawing.characterSytel.strike) {
        uint8_t nBitA = (gstDrawing.pstandFont->h >> 1);
        uint8_t nBitA1 = 0x01 << ((nBitA - 2)&7);
        uint8_t nBitA2 = 0x01 << ((nBitA + 2)&7);
        uint8_t nByte = nBitA >> 3;
        uint8_t maxByte = ((gstDrawing.pstandFont->h + 7)) >> 3;
        for (uint8_t i = 0; i < gstDrawing.pstandFont->w; i++) {
            uint8_t Index = i * maxByte + nByte;
            gu8CurrentCharsBitmap[Index] |= (nBitA1 | nBitA2);
        }

    }


    if (gstDrawing.characterSytel.blod) {
        uint8_t nBytePerRow = (gstDrawing.pstandFont->h + 7) >> 3;
        uint8_t maxByte = 2 * nBytePerRow;
        for (uint8_t i = 1; i < (maxByte); i++) {
            gu8CurrentCharsBitmap[i] |= gu8CurrentCharsBitmap[i + nBytePerRow];
        }
    }







}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
static void DrawBitmapChars90(uint16_t maxWith, uint8_t RightSpace, uint16_t w, uint16_t h, uint8_t xSize, uint8_t ySize, uint8_t *bitmap) {
    uint16_t width = ySize * h;
    uint16_t maxLineWidth = gstDrawing.u16XPos + (width);
    if (maxLineWidth + RightSpace > maxWith) {
        gstVar.u8TabIndex = 0;
        (void) putDataAction();
        return;
    }


    uint16_t y2 = 0;
    uint16_t x2 = 0;


    uint16_t color = 0;
    uint16_t mask = 0;
    uint16_t byteIndex = 0;
    uint16_t rowIndex = 0;
    uint16_t startY = gstDrawing.u16MaxLine - (w * xSize);

    uint16_t nByteBitmap = ((h + 7) >> 3);
    uint16_t row_bytes = ((gstDrawing.u16MaxDotLine + 7) >> 3);
    for (uint16_t j = startY; j < gstDrawing.u16MaxLine; j++) {
        uint16_t dividY = (y2 / ySize);
        mask = (0x01 << (dividY & 7));
        byteIndex = (dividY >> 3);
        rowIndex = j*row_bytes;
        x2 = 0;
        for (uint16_t i = gstDrawing.u16XPos; i < maxLineWidth; i++) {
            color = (bitmap[((x2 / xSize) * (nByteBitmap) + byteIndex)]) & mask;
            if (color) {
                gu8DrawBuffer[(i >> 3) + (rowIndex)] |= (0x80 >> (i & 7));
            }
            x2++;
        }

        y2++;
    }
    gstDrawing.u16XPos += (width);
    gstDrawing.u16YPos = MAX(gstDrawing.u16YPos, w * xSize);
    ReadCurrentCmd();
}

