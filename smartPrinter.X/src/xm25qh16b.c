
#include "gd32f30x_gpio.h"
#include <stddef.h>
#include <string.h>

#include <AllFilesInc.h>
#include <stdint-gcc.h>

#define DUMMY_BYTE                   0xA5

#define  SPI_FLASH_CS_PORTx            GPIOA
#define  SPI_FLASH_CS_PINx             GPIO_PIN_15

#define  SPI_FLASH_DATA_PORTx          GPIOC
#define  SPI_FLASH_SCK_PINx             GPIO_PIN_10


#define  SPI_FLASH_DI_PINx             GPIO_PIN_11
#define  SPI_FLASH_DO_PINx             GPIO_PIN_12


#define MIN(x,y)            (x<=y)?x:y

#define SPI_TIME_OUT                  100




#define  PAGE_WRITE_TIME_OUT          3U
#define  SECTOR_ERASE_TIME_OUT        200U
#define  BLOCK_ERASE_TIME_OUT         1000U
#define  CHIP_ERASE_TIME_OUT          50000U



#define MAX_SIZE_OF_DATA                 0x1FFFFF
///< Chip selection wait count
#define XM25QH16B_CS_WAIT_TIME           (1U)

#define FLASH_PAGE_SIZE             256U
#define FLASH_SECTOR_SIZE          4096U

#define SPI2_NSS_HIGH               gpio_bit_set(SPI_FLASH_CS_PORTx, SPI_FLASH_CS_PINx);
#define SPI2_NSS_LOW                gpio_bit_reset(SPI_FLASH_CS_PORTx, SPI_FLASH_CS_PINx);


typedef void(*pFunCurrentCommnd)(void);

typedef union {
    uint32_t u32Address;
    uint8_t u8address[4];
} utAddress_t;

typedef enum {
    WriteStatusReg1 = 0x01,
    ReadId = 0x90,
    ReadStatusReg1 = 0x05,
    WriteEnable = 0x06,
    WriteDisable = 0x04,
    ChipErase = 0x60,
    SectorErase = 0x20,
    BlockErase = 0xD8,
    PagePgm = 0x02,
    Read = 0x03,
    FastRead = 0x0Bu,
} en_Flash_CMD_t;

typedef struct {
    /*input flags*/
    uint8_t ready_flag;
    uint8_t busy_flag;
    uint8_t rw_flag;
    uint8_t Write_flag; /*output flags*/
    uint8_t error_flag;
    uint8_t receive_flag;
    uint8_t WriteState;
    uint8_t PageW;
    uint8_t WriteSector;
} ut_driver_flags_t;

typedef struct {
    utAddress_t utAddress;
    uint32_t u32DataSize;
    uint32_t u32TimeOut;
    uint32_t u32Index;
    uint16_t u16offset;
    uint16_t u16sectorCount;
    uint16_t u16SectorIndex;
    uint16_t u16StartSize;
    uint16_t u16EndSize;
    uint8_t *pu8Data;
    uint8_t *pu8WriteData;
    uint8_t u8PageIndex;
    uint8_t u8AddressSize;
    uint8_t u8TransmitState;
} st_flash_data_t;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : sector Buffer
 ---------------------------------------------------------------------------------------------------
 */
static uint8_t gu8SectorBuffer[FLASH_SECTOR_SIZE];
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash Flags
 ---------------------------------------------------------------------------------------------------
 */
static ut_driver_flags_t gutflashFlags;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash data
 ---------------------------------------------------------------------------------------------------
 */
static st_flash_data_t gstFlashData;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : status Register 
 ---------------------------------------------------------------------------------------------------
 */
static stTimer_TimeOut_t gstFlashTimeOut;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : status Register 
 ---------------------------------------------------------------------------------------------------
 */
static stTimer_TimeOut_t gstSPITimeOut;



static pFunCurrentCommnd gpFunCurrentCommand;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : prototype functions 
 ---------------------------------------------------------------------------------------------------
 */
static void start_spi_operation();
static void stop_spi_operation();
static void stop_spi_interrupt();
static void start_spi_interrupt();
static void flash_writeEnable();
static void flash_writeDisable();
static void writePage();
static void erase_block();
static void erase_sector();
static void erase_chip();
static void readData();
static void WriteStatusReg();
static void nextstep(uint32_t currentSize, uint8_t nextStep, uint8_t sendFirstByte);
static void flash_nss_delay();
static void writeDataOperation();
static void memOperation();
static void ResetDriver();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash Received Data handler
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void isr_spi2_receiver(void) {

    uint16_t value = 0x0001;
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    /*remove last byte {CMD,A3,A2,A1,A0,D0,D1,D2,....Dn} when write*/
    /*remove last byte {CMD,A3,A2,A1,A0,DUMY0,DUMY0,DUMY0,....DUMYn} when read*/
    value = spi_i2s_data_receive(SPI2);
    switch (gstFlashData.u8TransmitState) {
        case 0:
            nextstep(gstFlashData.u8AddressSize, 1, 1);
            break;
        case 1:/*send address*/
            gstFlashData.u32Index--;
            spi_i2s_data_transmit(SPI2, gstFlashData.utAddress.u8address[gstFlashData.u32Index]);
            if (gstFlashData.u32Index == 0) {
                if (gutflashFlags.rw_flag) {
                    gutflashFlags.receive_flag = 1;
                    nextstep(gstFlashData.u32DataSize, 3, 0);
                } else {
                    nextstep(gstFlashData.u32DataSize, 2, 0);
                }
            }
            break;
        case 2:/*send Data*/
            spi_i2s_data_transmit(SPI2, *(gstFlashData.pu8Data + gstFlashData.u32Index));
            gstFlashData.u32Index++;
            if (gstFlashData.u32Index >= gstFlashData.u32DataSize) {
                gstFlashData.u32Index = 0;
                nextstep(0, 0, 0);

            }
            break;
        case 3:/*send dummy*/
            spi_i2s_data_transmit(SPI2, (uint16_t) DUMMY_BYTE);
            if (gutflashFlags.receive_flag) {
                gstFlashData.u8TransmitState = 5;
            } else {
                gstFlashData.u8TransmitState = 4;
            }
            break;
        case 4:/*receive Data*/
            if ((value & 0x0001) == 0x0000) {

                gutflashFlags.error_flag = 0;
                gstFlashData.u8TransmitState = 0;
                stop_spi_interrupt();
                gpFunCurrentCommand();
                return;
            }

            if (sysIsTimeoutMs(&gstFlashTimeOut) == true) {

                gutflashFlags.error_flag = 1;
                gstFlashData.u8TransmitState = 0;
                gutflashFlags.ready_flag = 1;
                stop_spi_interrupt();
                return;
            }
            spi_i2s_data_transmit(SPI2, (uint16_t) DUMMY_BYTE);
            break;
        case 5:/*receive data*/
            if (gstFlashData.u32Index < gstFlashData.u32DataSize) {
                gstFlashData.pu8Data[gstFlashData.u32Index] = (uint8_t) value;
                gstFlashData.u32Index++;
                spi_i2s_data_transmit(SPI2, (uint16_t) DUMMY_BYTE);
            } else {
                gstFlashData.u8TransmitState = 0;
                gstFlashData.u32Index = 0;
                gutflashFlags.error_flag = 0;
                stop_spi_interrupt();
                gpFunCurrentCommand();
            }
            break;
        default:
            gstFlashData.u8TransmitState = 0;
            gstFlashData.u32Index = 0;
            gutflashFlags.error_flag = 1;
            stop_spi_interrupt();
            break;
    }

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Local function prototypes ('static')
 ---------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash Init Hardware of spi configurations
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
static void flash_memory_spi_Init() {

    spi_parameter_struct spi_init_struct;
    /*Enable SPI 2 Remap*/
    rcu_periph_clock_enable(RCU_SPI2);
    /*Enable SPI 2 Remap*/
    gpio_pin_remap_config(GPIO_SPI2_REMAP, ENABLE);
    /* SPI2 GPIO config: NSS/PA15*/
    gpio_pin_remap_config(GPIO_SWJ_DISABLE_REMAP, ENABLE);
    gpio_init(SPI_FLASH_CS_PORTx, GPIO_MODE_OUT_OD, GPIO_OSPEED_MAX, SPI_FLASH_CS_PINx);
    /*SPI2 GPIO config:MISCK/PC10*/
    gpio_init(SPI_FLASH_DATA_PORTx, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, SPI_FLASH_SCK_PINx);
    /* SPI2 GPIO config :  MOSI/PC12 */
    gpio_init(SPI_FLASH_DATA_PORTx, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, SPI_FLASH_DO_PINx);
    /* SPI2 GPIO config: MISO/PC11  DI*/
    gpio_init(SPI_FLASH_DATA_PORTx, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, SPI_FLASH_DI_PINx);
    SPI2_NSS_HIGH;
    /* SPI2 parameter config */
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_2;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    /* SPI int enable */
    spi_init(SPI2, &spi_init_struct);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : wait For rise time and fill time of CS
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
static void flash_nss_delay() {
    for (uint8_t i = 0; i < 20; i++) {
        __NOP(); /*8.3 n*/
    }
}







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
void flash_init(void) {
    flash_memory_spi_Init();
    gstFlashData.u8TransmitState = 0;
    gstFlashData.u32Index = 0;
    gstFlashData.pu8Data = NULL;
    gstFlashData.utAddress.u32Address = 0;
    gstFlashData.u32DataSize = 0;
    gstFlashData.u8PageIndex = 0;
    gutflashFlags.ready_flag = 1;
    gutflashFlags.error_flag = 0;
    gutflashFlags.WriteSector = 0;
    gpFunCurrentCommand = ResetDriver;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : stop Spi OPeration
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: none
 */
static void stop_spi_operation() {
    spi_disable(SPI2);
    __NOP();
    SPI2_NSS_HIGH;
    flash_nss_delay();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : start Spi OPeration
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: none
 */
static void start_spi_operation() {
    SPI2_NSS_LOW;
    __NOP();
    spi_enable(SPI2);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : stop all Interrupt
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: none
 */
static void stop_spi_interrupt() {
    stop_spi_operation();
    spi_i2s_interrupt_disable(SPI2, SPI_I2S_INT_RBNE);
    nvic_irq_disable(SPI2_IRQn);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : start spi  transmit Interrupt
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: none
 */
static void start_spi_interrupt() {
    nvic_irq_enable(SPI2_IRQn, 0x00, 0x00);
    spi_i2s_interrupt_enable(SPI2, SPI_I2S_INT_RBNE);
    start_spi_operation();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  chip erase
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void flash_chip_erase(void) {
    gutflashFlags.ready_flag = 0;
    gutflashFlags.WriteState = 1;
    gpFunCurrentCommand = flash_writeEnable;
    gpFunCurrentCommand();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Block erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the block to be erase
 * 
 * @return:  none
 */
void flash_erase_block(uint32_t u32Address) {
    gutflashFlags.ready_flag = 0;
    gstFlashData.utAddress.u32Address = u32Address;
    gutflashFlags.WriteState = 3;
    gpFunCurrentCommand = flash_writeEnable;
    gpFunCurrentCommand();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Sector erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the sector to be erase
 * 
 * @return: none
 */
void flash_write_status_Registers(uint8_t Reg1, uint8_t Reg2, uint8_t Reg3) {
    gutflashFlags.ready_flag = 0;
    gstFlashData.utAddress.u8address[0] = Reg3;
    gstFlashData.utAddress.u8address[1] = Reg2;
    gstFlashData.utAddress.u8address[2] = Reg1;
    gutflashFlags.WriteState = 4;
    gpFunCurrentCommand = flash_writeEnable;
    gpFunCurrentCommand();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Sector erase
 ---------------------------------------------------------------------------------------------------
 *  @param : Address of the sector to be erase
 * 
 * @return: none
 */
void flash_erase_sector(uint32_t u32Address) {
    gutflashFlags.ready_flag = 0;
    gstFlashData.utAddress.u32Address = u32Address;
    gutflashFlags.WriteState = 2;
    gpFunCurrentCommand = flash_writeEnable;
    gpFunCurrentCommand();
}

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
void flash_read_data(uint8_t *pbuffer, uint32_t u32Address, uint32_t u32size) {
    /*only worked command*/
    gutflashFlags.ready_flag = 0;
    gstFlashData.utAddress.u32Address = u32Address;
    gstFlashData.pu8Data = pbuffer;
    gstFlashData.u32DataSize = u32size;
    gpFunCurrentCommand = readData;
    gpFunCurrentCommand();
}

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
void flash_write_data(uint8_t *pbuffer, uint32_t u32Address, uint32_t u32size) {
    gstFlashData.u16offset = (u32Address & (FLASH_SECTOR_SIZE - 1));
    gstFlashData.u16StartSize = MIN(u32size, (FLASH_SECTOR_SIZE - gstFlashData.u16offset));
    gstFlashData.u16sectorCount = ((u32size - gstFlashData.u16StartSize) / FLASH_SECTOR_SIZE);
    gstFlashData.u16EndSize = ((u32size - gstFlashData.u16StartSize)) & (FLASH_SECTOR_SIZE - 1);


    if (gstFlashData.u16EndSize) {
        gstFlashData.u16sectorCount++;
    }

    if (gstFlashData.u16StartSize) {
        gstFlashData.u16sectorCount++;
    }
    gstFlashData.utAddress.u32Address = u32Address & ~(FLASH_SECTOR_SIZE - 1); /*First sector Address of the Data*/
    gstFlashData.pu8WriteData = pbuffer;
    gutflashFlags.WriteSector = 1;
    gstFlashData.u16SectorIndex = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : General mem Operation
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
static void memOperation() {


    if (gutflashFlags.ready_flag) {
        return;
    }

    if (gutflashFlags.ready_flag == 0) {
        if (sysIsTimeoutMs(&gstSPITimeOut) == true) {

            gutflashFlags.error_flag = 1;
            gutflashFlags.WriteSector = 0;
            gutflashFlags.ready_flag = 1;
            gstFlashData.u8TransmitState = 0;
            gstFlashData.u32Index = 0;
            gpFunCurrentCommand = ResetDriver;
            stop_spi_interrupt();
            return;
        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Flash memory background task
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
void FlashMemoryDriver() {
    memOperation();
    writeDataOperation();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get the Flash is Ready Or not
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 is busy , 1 is Ready
 */
uint8_t flash_ready() {
    if (gutflashFlags.ready_flag == 0) {
        return (0);
    }

    if (gutflashFlags.WriteSector) {
        return (0);
    }

    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : get flash last operation state
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 no error , 1 have error
 */
uint8_t flash_error() {
    uint8_t temp;
    temp = gutflashFlags.error_flag;
    gutflashFlags.error_flag = 0;
    gpFunCurrentCommand = ResetDriver;
    gutflashFlags.ready_flag = 1;
    return temp;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :Write Enable Command 
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  0 no error , 1 have error
 */
static void flash_writeEnable() {

    switch (gutflashFlags.WriteState) {
        case 0:
            if (gutflashFlags.PageW) {
                gutflashFlags.PageW = 0;
                gstFlashData.utAddress.u32Address += FLASH_PAGE_SIZE;
                gstFlashData.pu8Data += FLASH_PAGE_SIZE;
            }
            gpFunCurrentCommand = writePage;

            break;
        case 1:
            gpFunCurrentCommand = erase_chip;

            break;
        case 2:
            gpFunCurrentCommand = erase_sector;

            break;
        case 3:
            gpFunCurrentCommand = erase_block;
            break;
        case 4:
            gpFunCurrentCommand = WriteStatusReg;
            break;
        default:
            return;
            break;
    }

    gutflashFlags.busy_flag = 0;
    gutflashFlags.rw_flag = 0; /*don't care*/
    /*only worked command*/
    gstFlashData.u8AddressSize = 0;
    gstFlashData.u32DataSize = 0;
    /*Time out Driver*/
    start_spi_interrupt();
    /*enable system Time Out*/
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    spi_i2s_data_transmit(SPI2, (uint16_t) WriteEnable);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : write Disable Command
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void flash_writeDisable() {
    gutflashFlags.busy_flag = 0;
    gutflashFlags.rw_flag = 0; /*don't care*/
    /*only worked command*/
    gstFlashData.u8AddressSize = 0;
    gstFlashData.u32DataSize = 0;
    gutflashFlags.Write_flag = 0;

    gpFunCurrentCommand = ResetDriver;
    /*Time out Driver*/
    start_spi_interrupt();
    /*enable system Time Out*/
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    spi_i2s_data_transmit(SPI2, (uint16_t) WriteDisable);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : read data callback
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void readData() {
    gutflashFlags.busy_flag = 0;
    gutflashFlags.rw_flag = 1;
    gstFlashData.u8AddressSize = 3;
    gpFunCurrentCommand = ResetDriver;
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    start_spi_interrupt();
    spi_i2s_data_transmit(SPI2, (uint16_t) Read);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : write Data Callback
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void writePage() {



    if (gstFlashData.u8PageIndex > 0) {
        gutflashFlags.busy_flag = 1;
        gutflashFlags.rw_flag = 0;

        /*only worked command*/
        gstFlashData.u8AddressSize = 3;
        gstFlashData.u32DataSize = FLASH_PAGE_SIZE;
        gstFlashData.u32TimeOut = PAGE_WRITE_TIME_OUT;
        gstFlashData.u8PageIndex--;

        if (gstFlashData.u8PageIndex == 0) {
            gutflashFlags.PageW = 0;
            gpFunCurrentCommand = flash_writeDisable;
        } else {
            gpFunCurrentCommand = flash_writeEnable;
            gutflashFlags.PageW = 1;
        }
        /*enable system Time Out*/
        start_spi_interrupt();
        sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);

        spi_i2s_data_transmit(SPI2, (uint16_t) PagePgm);
        return;
    }


    /*enable system Time Out*/
    gutflashFlags.PageW = 0;
    gpFunCurrentCommand = flash_writeDisable;

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : write the status Register
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void WriteStatusReg() {
    gutflashFlags.busy_flag = 1;
    gutflashFlags.rw_flag = 0; /*don't care*/

    /*only worked command*/
    gstFlashData.u8AddressSize = 3;
    gstFlashData.u32DataSize = 0;
    /*Time out Driver*/
    gpFunCurrentCommand = flash_writeDisable;
    start_spi_interrupt();
    /*enable system Time Out*/
    gstFlashData.u32TimeOut = BLOCK_ERASE_TIME_OUT;
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    spi_i2s_data_transmit(SPI2, (uint16_t) WriteStatusReg1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Erase block Callback
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void erase_block() {
    gutflashFlags.busy_flag = 1;
    gutflashFlags.rw_flag = 0; /*don't care*/
    /*only worked command*/
    gstFlashData.u8AddressSize = 3;
    gstFlashData.u32DataSize = 0;
    /*Time out Driver*/
    gpFunCurrentCommand = flash_writeDisable;
    start_spi_interrupt();
    /*enable system Time Out*/
    gstFlashData.u32TimeOut = BLOCK_ERASE_TIME_OUT;
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    spi_i2s_data_transmit(SPI2, (uint16_t) BlockErase);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Erase block Callback
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void erase_sector() {
    gutflashFlags.busy_flag = 1;
    gutflashFlags.rw_flag = 0; /*don't care*/
    /*only worked command*/
    gstFlashData.u8AddressSize = 3;
    gstFlashData.u32DataSize = 0;
    /*enable system Time Out*/

    gpFunCurrentCommand = flash_writeDisable;
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    gstFlashData.u32TimeOut = SECTOR_ERASE_TIME_OUT;
    start_spi_interrupt();
    spi_i2s_data_transmit(SPI2, (uint16_t) SectorErase);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Erase block Callback
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return: 
 */
static void erase_chip() {
    gutflashFlags.busy_flag = 1;
    gutflashFlags.rw_flag = 0; /*don't care*/
    /*only worked command*/
    gstFlashData.u8AddressSize = 0;
    gstFlashData.u32DataSize = 0;
    gpFunCurrentCommand = flash_writeDisable;
    /*enable system Time Out*/
    sysSetPeriodMS(&gstSPITimeOut, SPI_TIME_OUT);
    gstFlashData.u32TimeOut = CHIP_ERASE_TIME_OUT;
    start_spi_interrupt();
    spi_i2s_data_transmit(SPI2, (uint16_t) ChipErase);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Erase block Callback
 ---------------------------------------------------------------------------------------------------
 *  @param : current size to send
 * 
 *  @param :current buffer to be send
 * 
 * @param : next step
 * 
 * @param : first byte is send or not 
 * 
 * @return: 
 */
static void nextstep(uint32_t currentSize, uint8_t nextStep, uint8_t sendAddress) {
    if (currentSize != 0) {
        gstFlashData.u8TransmitState = nextStep;
        if (sendAddress) {
            gstFlashData.u32Index = gstFlashData.u8AddressSize - 1;
            spi_i2s_data_transmit(SPI2, (uint16_t) gstFlashData.utAddress.u8address[gstFlashData.u32Index]);
        }
    } else if (gutflashFlags.busy_flag != 0) {
        gutflashFlags.receive_flag = 0;
        stop_spi_operation();
        start_spi_operation();
        sysSetPeriodMS(&gstFlashTimeOut, gstFlashData.u32TimeOut);
        gstFlashData.u8TransmitState = 3;
        spi_i2s_data_transmit(SPI2, (uint16_t) ReadStatusReg1);
    } else {
        gstFlashData.u8TransmitState = 0;
        gutflashFlags.error_flag = 0;
        stop_spi_interrupt();
        gpFunCurrentCommand();
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : General  Write Operation
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
static void writeDataOperation() {
    uint16_t u16NumberOfSectors;
    uint16_t u16SectorIndex;
    if (gutflashFlags.ready_flag == 0) {
        return;
    }
    switch (gutflashFlags.WriteSector) {
        case 0:
            break;
        case 1:
            if (gstFlashData.u16SectorIndex < gstFlashData.u16sectorCount) {
                flash_read_data(gu8SectorBuffer, gstFlashData.utAddress.u32Address, FLASH_SECTOR_SIZE);
                gutflashFlags.WriteSector = 2;
                return;
            }
            gutflashFlags.WriteSector = 0;
            gstFlashData.u16SectorIndex = 0;
            break;
        case 2:
            /*Edit Data*/
            if ((gstFlashData.u16SectorIndex == 0) && (gstFlashData.u16StartSize)) {
                copyBuff(gu8SectorBuffer + gstFlashData.u16offset, gstFlashData.pu8WriteData, gstFlashData.u16StartSize);
            } else if ((gstFlashData.u16SectorIndex == (gstFlashData.u16sectorCount - 1)) && (gstFlashData.u16EndSize)) {

                u16NumberOfSectors = (gstFlashData.u16sectorCount - (((gstFlashData.u16StartSize > 0) ? 2U : 1U)));
                copyBuff(gu8SectorBuffer, gstFlashData.pu8WriteData + (gstFlashData.u16StartSize)+(u16NumberOfSectors * FLASH_SECTOR_SIZE), gstFlashData.u16EndSize);
            } else {
                u16SectorIndex = (gstFlashData.u16StartSize > 0) ? (gstFlashData.u16SectorIndex - 1) : (gstFlashData.u16SectorIndex);
                copyBuff(gu8SectorBuffer, gstFlashData.pu8WriteData + gstFlashData.u16StartSize + (u16SectorIndex * FLASH_SECTOR_SIZE), FLASH_SECTOR_SIZE);
            }
            flash_erase_sector(gstFlashData.utAddress.u32Address);
            gutflashFlags.WriteSector = 3;
            break;
        case 3:
            /*write sector*/
            gstFlashData.pu8Data = (uint8_t *) gu8SectorBuffer;
            gstFlashData.u32DataSize = FLASH_SECTOR_SIZE;
            gutflashFlags.ready_flag = 0;
            gstFlashData.u8PageIndex = (FLASH_SECTOR_SIZE / FLASH_PAGE_SIZE);
            gutflashFlags.WriteState = 0;
            gpFunCurrentCommand = flash_writeEnable;
            gpFunCurrentCommand();
            gutflashFlags.WriteSector = 4;
            break;
        case 4:
            gstFlashData.utAddress.u32Address += FLASH_PAGE_SIZE;
            /*First sector Address of the Data*/;
            gstFlashData.u16SectorIndex++;
            gutflashFlags.WriteSector = 1;
            break;
        default:
            gutflashFlags.WriteState = 0;
            break;
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Ready Function
 ---------------------------------------------------------------------------------------------------
 *  @param : none
 * 
 * @return:  none
 */
static void ResetDriver() {
    gutflashFlags.ready_flag = 1;

}