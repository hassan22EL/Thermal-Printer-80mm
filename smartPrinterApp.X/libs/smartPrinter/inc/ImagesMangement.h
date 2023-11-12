/* 
 * File:   ImagesMangement.h
 * Author: hassa
 *
 * Created on September 10, 2023, 6:23 PM
 */

#ifndef IMAGESMANGEMENT_H
#define	IMAGESMANGEMENT_H


#define          IMAGES_MEMORY_SIZE                    256U*1024U  

typedef union {
    uint32_t size;

    struct {
        unsigned Xsize : 4;
        unsigned Ysize : 4;
        unsigned Index : 8;
    };
} st_Bit_image_size_t;

typedef struct {
    uint32_t u32Address;
    uint16_t h;
    uint16_t w;
    st_Bit_image_size_t Size; /*4Bit*/

} BitImageHeader_t;

#define MAX_BUFFER                3522U
#define MAX_LOGO                  47U 

typedef struct {
    uint8_t defineImageBuffer[MAX_BUFFER];
    BitImageHeader_t header[MAX_LOGO];
} st_BitImage_t;


/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init all variables in this buffer
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
void ImagesInit();
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
uint8_t loadCurrentIndex(uint8_t index, uint8_t m);
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : print Images 
 ---------------------------------------------------------------------------------------------------
 * @param :current line Print 
 * 
 * @parm : max lines prints
 * 
 * @return : none
 */
void DrawBitmap(int16_t currentLine, int16_t ypos);

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Print Image From memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
uint8_t PrintNvImage();
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : save data into memory
 ---------------------------------------------------------------------------------------------------
 * @param :none
 * 
 * @return : none
 */
uint8_t saveNvImage(stByteFIFO_t *pReceiveBuffer);
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
uint8_t upLoadHeaders();
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
uint8_t BitNVImagesIsRead();
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
uint8_t setMaxLogo(uint8_t MaxLog);

#endif	/* IMAGESMANGEMENT_H */

