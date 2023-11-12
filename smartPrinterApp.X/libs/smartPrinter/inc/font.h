/* 
 * File:   font.h
 * Author: hassa
 *
 * Created on August 2, 2023, 7:46 PM
 */

#ifndef FONT_H
#define	FONT_H

#include <stdint.h>
#include <fifo.h>

#define MAX_TAB_IN_LINE     32

#define        ROW_BITMAP                       0
#define        COLUMN_BITMAP                    1
#define        BITMAP_LSB                 (1)
#define        BITMAP_MSB                  (0)

typedef union {
    uint16_t u8DipSwitch;

    struct {
        unsigned cutter : 1;
        unsigned buzzer : 1;
        unsigned density : 1;
        unsigned byteMode : 1;
        unsigned chash_box : 1;
        unsigned buadrate : 3;
        unsigned autolineEnable : 1;
    };
} ut_dip_switch_t;
extern ut_dip_switch_t gutDipSwitch;

typedef union {
    uint32_t characterSytel;

    struct {
        unsigned underLine : 1;
        unsigned blod : 1;
        unsigned rotate90 : 1;
        unsigned xSize : 4;
        unsigned ySize : 4;
        unsigned justification : 2;
        unsigned copyJustification : 2;
        unsigned strike : 1;
        unsigned Characterfont : 2;
        unsigned whiteBlackMode : 1;
        unsigned upside_down : 1;
        unsigned CodePageSelect : 7;
    };
} utCharaterSytel_t;

typedef struct {
    uint16_t u16BitmapCharOffset;
    uint8_t u8Width;
    uint8_t u8Height;
    uint8_t u8Xadvance;
    int8_t u8XOffset;
    int8_t u8YOffset;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Base Data of the Font
 ---------------------------------------------------------------------------------------------------
 * @member : Char offset into font bitmaps
 * 
 * @member : Bitmap dimensions in pixels 
 * 
 * @member :Bitmap dimensions in pixels
 * 
 * @member : Distance to advance cursor (x axis)
 * 
 * @member : X dist from cursor pos to UL corner  
 * 
 * @member :Y dist from cursor pos to UL corner 
 */
st_cutomefontphy_t;

typedef struct {
    uint8_t *pu8Bitmap;
    st_cutomefontphy_t *pstFontPhy;
    uint16_t u16FirstChar;
    uint16_t u16LastChar;
    int8_t u8Yadvance;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Font Data
 ---------------------------------------------------------------------------------------------------
 * @member : Pointer of bit maps buffer
 * 
 * @member : Pointer array of Base Data of the font  
 * 
 * @member : ASCII extents (first char)
 * 
 * @member : ASCII extents (last char)
 * 
 * @member : Newline distance (y axis)  
 * 
 */
st_customfont_t;

typedef struct {
    uint8_t *pu8Bitmap;
    uint32_t w;
    uint32_t h;
    uint32_t NBytePerChar;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Font Data
 ---------------------------------------------------------------------------------------------------
 * @member : Pointer of bit maps buffer
 * 
 * @member :  number of dot of with
 * 
 * @member : number of dot of hight
 * 
 */
st_standFont_t;
typedef struct {
    uint8_t *pu8Buffer;
    uint8_t u8wFlag;
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Font Data
 ---------------------------------------------------------------------------------------------------
 * @member : Pointer of bit maps buffer
 * 
 * @member :  Read and Write Flag
 * 
 */
st_sPointers_t;

typedef struct {
    utCharaterSytel_t characterSytel;
    st_standFont_t *pstandFont;
    st_sPointers_t gstPointer[2];
    uint16_t u16LineSpace;
    uint16_t u16MaxDotLine;
    uint16_t u16MaxLine;
    uint16_t u16XPos;
    uint16_t u16YPos;
    uint16_t i16LeftMargin;
    uint8_t u8CharRightSpace;
    
    
}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  DrawingData
 ---------------------------------------------------------------------------------------------------
 * @member : max dont ber in line 
 * 
 * @member : max line per char 
 * 
 * @member : with by modified by current rotation
 * 
 * @member : hight by modified by current rotation
 * 
 * @member : x location to start printing text
 * 
 * @member : y location to start printing text
 * 
 * @member : text size in X
 *  
 * @member : text size in Y
 * 
 * @member : text warp
 * 
 * @member :  Pointer to special font
 * 
 * @member : Pointer to Pixel buffer
 */
st_drawing_t;




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
void PixelBufferInit(uint16_t maxPixel, uint16_t maxLine);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Delete Frame Buffer (Pixel Buffer)
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void PixelBufferDeinit();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set current Position
 ---------------------------------------------------------------------------------------------------
 *  @param : x coordinate
 * 
 *  @param :y coordinate
 * 
 * @return:  void
 */
void setDrawingCurrentPos(int16_t x, int16_t y);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set code page character set
 ---------------------------------------------------------------------------------------------------
 *  @param : code page number 
 * 
 * @return:  void
 */
void setDrawingCPSet(uint8_t cpSet);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set rotation setting for display
 ---------------------------------------------------------------------------------------------------
 *  @param : 0 thru 3 corresponding to 4 cardinal rotations
 * 
 * @return:  current with
 */
void setDrawingRotaion90(uint8_t Enable);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current x position 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current x position
 */
int16_t getDrawingCurrentXPos();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current x position 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current y position
 */
int16_t getDrawingCurrentYPos();


/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  fill buffer by one or zero
 ---------------------------------------------------------------------------------------------------
 * @param:  color Binary (on or off) color to fill with 
 * 
 * @return : none
 * 
 */
void fillBuffer(uint8_t color);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Fill a all Printable area completely with one color. 
 ---------------------------------------------------------------------------------------------------
 * @param : fill value 0 or one
 */
void fillScreen(uint8_t color);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : change current fonts 
 ---------------------------------------------------------------------------------------------------
 * @param : Pointer to current stander fonts
 * 
 * @return : none
 */
void assignemtNewFont(st_standFont_t *standFont);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Current Data is bold or not
 ---------------------------------------------------------------------------------------------------
 * @param : Blod state flag 0: is normal 1:is bold
 */
void drawCharActiveBlodState(uint8_t En);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set rotation setting for display
 ---------------------------------------------------------------------------------------------------
 *  @param : 0 thru 3 corresponding to 4 cardinal rotations
 * 
 * @return:  current with
 */
void setDrawingCurrentRotaion(uint8_t x);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Write Current Char to Buffer
 ---------------------------------------------------------------------------------------------------
 * @param : charrent char
 */
void WriteChar(uint8_t c);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size X
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDrawingSizeX(uint8_t x);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size Y
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDrawingSizeY(uint8_t y);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Print Now Data
 ---------------------------------------------------------------------------------------------------
 * @param : pointer 
 * 
 * @param : none
 * 
 * @return:none
 */
void TestCode();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Text Size Y
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void SetupSideDown(uint8_t Value);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set space between char
 ---------------------------------------------------------------------------------------------------
 * @param : number of dot
 * 
 * @return:none
 */
void setSpaceBetweenChar(uint8_t n);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get State of the Line Feed
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
uint8_t getAutoLineFiedFlag();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Font
 ---------------------------------------------------------------------------------------------------
 *  @param : Current Font Select
 * 
 * @return:  current with
 */
void setCurrentFont(uint8_t Font);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Bold
 ---------------------------------------------------------------------------------------------------
 *  @param : Current Char is bold Select
 * 
 * @return:  current with
 */
void setCurrentBold(uint8_t bold);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current under Line
 ---------------------------------------------------------------------------------------------------
 *  @param : number of dot to under line Data
 * 
 * @return:  current with
 */
void setCurrentUnderLine(uint8_t nDon);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set Left Margin of the Printer
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void setLeftMargin(int16_t leftMargin);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set default line space
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current with
 */
void setDefaultLineSpace(void);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Set rotation setting for display
 ---------------------------------------------------------------------------------------------------
 *  @param : set line space value
 * 
 * @return:  current with
 */
void setLineSpace(uint16_t vaule_per_dot);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Font
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current Font select
 */
uint8_t getCurrentFont(void);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set current Font
 ---------------------------------------------------------------------------------------------------
 *  @param : Current Font Select
 * 
 * @return:  current with
 */
void setCurrentFont(uint8_t Font);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void WriteBitImage(uint8_t m, uint16_t width, stByteFIFO_t *BitImage);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Fill the Tab Option
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
uint8_t fillTabBuffer(uint8_t value, uint8_t Index);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set Tab Process
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void TabPorcess();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : set Tab to default values
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void Default_Tab_set();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set double strike
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setDoubleStrike(uint8_t value);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  set justification Value
 ---------------------------------------------------------------------------------------------------
 *  @param : 1-->to 8
 * 
 * 
 * @return:  void
 */
void setJustification(uint8_t Value);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get The Current Hight
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * 
 * @return:value of max Hight
 */
uint8_t getTheLineHaveAData();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current x position 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  current y position
 */
uint16_t getLineSpace();

/*
---------------------------------------------------------------------------------------------------
 * @brief : set Absolute x postion
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  void
 */
void setAbsoluteXPostion(uint16_t xpos);
/*
---------------------------------------------------------------------------------------------------
 * @brief : set Relative x postion
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  void
 */
void setRelativeXPostion(uint16_t xpos);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read One Line From i
 ---------------------------------------------------------------------------------------------------
 * @param : current line Index
 * 
 * @param : destination buffer
 * 
// * @param : max line copy
 * 
 * 
 * @return:none
 */
uint8_t * getLineFromPuffer(uint8_t max);
/*
---------------------------------------------------------------------------------------------------
 * @brief : Reset
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  void
 */
void ResetWriteClearFlag();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get current font data
 ---------------------------------------------------------------------------------------------------
 * @param : font Index
 * 
 * @return: Pointer to font
 */
st_standFont_t * getCurrentstandFont(uint8_t value);
/*
---------------------------------------------------------------------------------------------------
 * @brief  : Write Current Char to Buffer
---------------------------------------------------------------------------------------------------
 * @param : charrent char
 */
void WriteChar(uint8_t c);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  write Bit Image 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return:none
 */
void WriteBitImage(uint8_t m, uint16_t width, stByteFIFO_t *BitImage);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get value of the y
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : return current Data Pos
 *
 */
uint16_t getLastDataYpos();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get The Current Hight
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * 
 * @return:value of max Hight
 */
uint8_t PrintBufferHasData();
/*
---------------------------------------------------------------------------------------------------
 * @brief : put action 
---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 or one 
 */
uint8_t putDataAction();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  get Pixel From Bitmap
 ---------------------------------------------------------------------------------------------------
 * @param :  x -axis
 *  
 * @param : y -axis
 * 
 * @param: witdh of the bit map
 * 
 * @param : hight of the bit map
 * 
 * @param : bitmap encode type {row or column}
 * 
 * @param :pointer bitmap data
 * 
 *@return : pixel color {0 is white , 1 is black}
 */
uint8_t getPixelFromBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t *bitmap, uint8_t LSB);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Reset Write Flag
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 *@return :none
 */
void ResetWriteReady();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : check to Print width
 ---------------------------------------------------------------------------------------------------
 * @param  : start Line to be movement
 * 
 * @param : max Line to be movement to x
 * 
 * @return:none
 */
void JustificationOperation();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : switch Write Index
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 *
 */ 
 void  switchWriteIndex();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : switch Read Index
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 *
 */
void switchReadIndex();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Get max line in buffer
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : max dot line
 *
 */
uint16_t getMaxLine();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : switch Read Index
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 *
 */
uint8_t chaekReadFlag();

uint8_t getupSizeDown();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get max number of dot per line 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: max number of dot per line 
 */
uint16_t getMaxDotPerLine() ;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  :get read flag
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
uint8_t GetReadFlag();
#endif	/* FONT_H */

