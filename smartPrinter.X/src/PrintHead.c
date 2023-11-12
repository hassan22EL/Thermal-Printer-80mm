/*main file of the print head*/



#include <system.h>
#include <type.h>
#include <gd32f30x_timer.h>
#include <gd32f30x_spi.h>
#include <stddef.h>

#include <string.h>
#include <AllFilesInc.h>
#include <stdint-gcc.h>



static const uint16_t gu8StepTime[] = {
    6250,
    3750,
    2916,
    2467,
    2176,
    1968,
    1810,
    1685,
    1582,
    1496,
    1423,
    1359,
    1303,
    1253,
    1209,
    1169,
    1133,
    1100,
    1069,
    1041,
    1015,
    991,
    968,
    947,
    927,
    908,
    890,
    873,
    857,
    842,
    828,
    814,
    801,
    788,
    776,
    764,
    753,
    742,
    732,
    722,
    713,
    704,
    695,
    686,
    678,
    670,
    662,
    654,
    647,
    640,
    633,
    626,
    620,
    614,
    608,
    602,
    596,
    590,
    584,
    579,
    574,
    569,
    564,
    559,
    554,
    549,
    544,
    539,
    535,
    531,
    527,
    523,
    519,
    515,
    511,
    507,
    503,
    499,
    495,
    491,
    487,
    484,
    481,
    478,
    475,
    472,
    469,
    466,
    463,
    460,
    457,
    454,
    451,
    448,
    445,
    442,
    439,
    436,
    433,
    430,
    427,
    424,
    421,
    418,
    415,
    413,
    411,
    409,
    407,
    405,
    403,
    401,
    399,
    397,
    395,
    393,
    391,
    389,
    387,
    385,
    383,
    381,
    379,
    377,
    375,
    373,
    371,
    369,
    367,
    365,
    363,
    361,
    359,
    357,
    355,
    353,
    351,
    349,
    347,
    345,
    343,
    341,
    339,
    337,
    335,
    333,
    331,
    329,
    327,
    325,
    323,
    321,
    319,
    317,
    315,
    313,
    311,
    310,
    309,
    308,
    307,
    306,
    305,
    304,
    303,
    302,
    301,
    300,
    297
};
static const uint8_t gu8Tempp[] = {
    /*80 dgree*/
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    79, 79, 79,
    78, 78, 78, 78,
    77, 77, 77, 77,
    76, 76, 76, 76,
    75, 75, 75, 75,
    74, 74, 74, 74,
    73, 73, 73, 73,
    72, 72, 72, 72, 72,
    71, 71, 71, 71,
    70, 70, 70, 70, 70,
    69, 69, 69, 69, 69,
    68, 68, 68, 68, 68,
    67, 67, 67, 67, 67,
    66, 66, 66, 66, 66,
    65, 65, 65, 65, 65,
    64, 64, 64, 64, 64, 64,
    63, 63, 63, 63, 63,
    62, 62, 62, 62, 62, 62,
    61, 61, 61, 61, 61, 61,
    60, 60, 60, 60, 60, 60,
    59, 59, 59, 59, 59, 59, 59,
    58, 58, 58, 58, 58, 58,
    57, 57, 57, 57, 57, 57, 57,
    56, 56, 56, 56, 56, 56, 56,
    55, 55, 55, 55, 55, 55, 55,
    54, 54, 54, 54, 54, 54, 54,
    53, 53, 53, 53, 53, 53, 53,
    52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    49, 49, 49, 49, 49, 49, 49, 49,
    48, 48, 48, 48, 48, 48, 48, 48,
    47, 47, 47, 47, 47, 47, 47, 47, 47,
    46, 46, 46, 46, 46, 46, 46, 46,
    45, 45, 45, 45, 45, 45, 45, 45, 45,
    44, 44, 44, 44, 44, 44, 44, 44, 44,
    43, 43, 43, 43, 43, 43, 43, 43, 43,
    42, 42, 42, 42, 42, 42, 42, 42, 42,
    41, 41, 41, 41, 41, 41, 41, 41, 41,
    40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
    39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
    38, 38, 38, 38, 38, 38, 38, 38, 38,
    37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
    34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
    33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
    23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
    22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
};

#define ADC_GPIO_PORT                           GPIOA
#define ADC_GPIO_PIN                           GPIO_PIN_3

#define ONE_RELUATION_DISTANCE                    ((STEP_DISTANCE * (360U))/(STEP_ANGLE*1000U))
#define DEFAULT_SPEED                             250U         
#define MIN_SPEED                                 50U
#define MAX_SPEED                                 410U
#define MAX_HEAT_TIME                             500U
#define MIN_HEAT_TIME                             200U
#define DEFAULT_HEAT_TIME                         300U




static const uint8_t gu8FeedPhase[4][2] = {
    {1, 1}, /**/
    {0, 1},
    {0, 0},
    {1, 0}
};

/*system Enabled */
typedef struct {
    uint32_t stepTime;
    uint16_t setHeatTime;
    uint16_t speed;
    uint16_t NByte;
    uint8_t stepRun;
    uint8_t HeatTimeRun;
    uint8_t headreverse;
    uint8_t u8State;
    uint8_t Pre;
    uint8_t Post;

}
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Print Head Main struct
 ---------------------------------------------------------------------------------------------------
 * @member : value of the feed speed
 * 
 * @member : Number of steps required
 * 
 * @member : step Time Value Per usec
 * 
 * @member : current setp Index
 *  
 * @memebr : distance between two line
 */
st_printhead_t;

#define MAX_ACTION                 256U

typedef struct {
    uint8_t LineBuffer[72];
} st_hardware_handel_drawing;

static uint16_t gsStepCounter = 0;
static uint32_t Timer_VALUE = 0U;


#if TESET_TIME
/*
 * <Struct Array of chars
 */
static uint32_t timebuffer[192];
uint32_t maxTime = 0;
uint32_t minTime = UINT32_MAX;
#endif
/*
 * <Struct Array of chars
 */
static uint8_t gu8MaxActions[MAX_ACTION * sizeof (st_hardware_handel_drawing)];
/*
 * Queue Buffer of struct
 */
static stStructFIFO_t gstFifoAction;

/*
 * Variables 
 */
static st_hardware_handel_drawing gstHardwareData;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Print Head values and 
 ---------------------------------------------------------------------------------------------------
 */
static st_printhead_t gstPrintHead;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : local function Declaration
 ---------------------------------------------------------------------------------------------------
 * @Fun     FeedLine    : just feed by number of line
 * 
 * @Fun     FeedSpace    : feed Head by line space 
 * 
 * @Fun    FeedStepTime   : get step time to Generate next Phase Time Per Usec
 * 
 * @Fun   printhead_writeLine : write Line by Line
 */
static void printhead_write_Data();
static void printhead_startHeat(void);


static void printhead_pins_init();
static void printhead_write_step();
static void HeatLoad(uint32_t _u32period_us);
static void StepperLoad(uint32_t _u32period_us, uint8_t autLeload);
static void Start_Heat_Timer();
static void Stop_Heat_Timer();
static void Stop_Stepper_Timer();
static void SPI0_Init();
static void adc_config();
static inline void adcEnable();
static inline void adcDisable();
static inline uint16_t adcReadData();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  :  Macro Phase
 ---------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Timer 3 Run Timer
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
void printhead_timer1_isr(void) {
    GPIO_BC(PRINTER_STB_PORTx) = (uint32_t) PRINTER_STB_PINx;
    Stop_Heat_Timer();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Timer 3 Run Timer
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
void printhead_timer2_isr(void) {
    /*feed*/

   
    uint32_t currentTime = 0;
    printhead_startHeat();
    switch (gstPrintHead.stepRun) {
        case 0:
            currentTime = gu8StepTime[gsStepCounter];
            if (currentTime <= gstPrintHead.stepTime) {
                gstPrintHead.stepRun = 1;
                StepperLoad(currentTime, 1);
                gsStepCounter = 0;
            } else {
                StepperLoad(currentTime, 0);
                gsStepCounter++;
            }
            break;
        case 1:/*run Case*/
            break;
        case 2:/**/
            break;
        default:
            break;
    }

    if (fifo_struct_Read(&gstFifoAction, &gstHardwareData) == FIFO_ERR_NO_DAT) {
        //get current Line
        Stop_Stepper_Timer();
        GPIO_BC(FEED_ENABLE_PORTx) = (uint32_t) FEED_ENABLE_PINx;
        gstPrintHead.stepRun = 0;
        
        gsStepCounter = 0;
        gstPrintHead.u8State = 0; /*go to First action Run*/
        if (getCutState()) {
            GPIO_BC(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;
        }
        return;
    }

    printhead_write_Data();
    printhead_write_step();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init all I/O Pins in this Driver
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
static void printhead_pins_init() {



    /*Head Power on*/
    /*Push Pull is apply data into */
    gpio_init(PRINTER_POWER_SW_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, PRINTER_POWER_SW_PINx);
    GPIO_BC(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;


    /*Push Pull is apply data into */
    gpio_init(FEED_ENABLE_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, FEED_ENABLE_PINx);
    GPIO_BC(FEED_ENABLE_PORTx) = (uint32_t) FEED_ENABLE_PINx;

    /*Init current Driver  Pin*/
    gpio_init(FEED_PHASESPEED_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, FEED_PHASESPEED_PINx);
    GPIO_BC(FEED_PHASESPEED_PORTx) = (uint32_t) FEED_PHASESPEED_PINx;

    /*Init  Phases {A,B}*/
    gpio_init(FEED_APHASE_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, FEED_APHASE_PINx);
    gpio_init(FEED_BPHASE_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, FEED_BPHASE_PINx);
    gpio_bit_write(FEED_APHASE_PORTx, FEED_APHASE_PINx, gu8FeedPhase[0][0]);
    gpio_bit_write(FEED_BPHASE_PORTx, FEED_BPHASE_PINx, gu8FeedPhase[0][1]);

    /*Init Sleep Pin*/
    gpio_init(FEED_SLEEP_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, FEED_SLEEP_PINx);
    GPIO_BOP(FEED_SLEEP_PORTx) = (uint32_t) FEED_SLEEP_PINx;


    gpio_init(PRINTER_LAT_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, PRINTER_LAT_PINx);
    GPIO_BOP(PRINTER_LAT_PORTx) = (uint32_t) PRINTER_LAT_PINx;

    /*Head STB PIN*/
    gpio_init(PRINTER_STB_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, PRINTER_STB_PINx);
    GPIO_BC(PRINTER_STB_PORTx) = (uint32_t) PRINTER_STB_PINx;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Write current step
 ---------------------------------------------------------------------------------------------------
 * @param : Direction 
 * 
 *@return : none 
 */
static void printhead_write_step() {
    static uint32_t currStep = 0;
    if (currStep >= TOTAL_STEP_PHASE) {
        currStep = 0;
    }

    if (RESET != gu8FeedPhase[currStep][0]) {
        GPIO_BOP(FEED_APHASE_PORTx) = (uint32_t) FEED_APHASE_PINx;
    } else {
        GPIO_BC(FEED_APHASE_PORTx) = (uint32_t) FEED_APHASE_PINx;
    }

    if (RESET != gu8FeedPhase[currStep][1]) {
        GPIO_BOP(FEED_BPHASE_PORTx) = (uint32_t) FEED_BPHASE_PINx;
    } else {
        GPIO_BC(FEED_BPHASE_PORTx) = (uint32_t) FEED_BPHASE_PINx;
    }

    currStep++;
}

static void HeatLoad(uint32_t _u32period_us) {
    TIMER_CAR(TIMER1) = ((_u32period_us * Timer_VALUE) - 1U);
}

static void StepperLoad(uint32_t _u32period_us, uint8_t autLeload) {
    /*Stop Timer*/
    TIMER_CTL0(TIMER2) &= ~(uint32_t) TIMER_CTL0_CEN;
    /*Stop Intrrupt*/
    TIMER_DMAINTEN(TIMER2) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_INTF(TIMER2) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_CAR(TIMER2) = ((_u32period_us * Timer_VALUE) - 1U);
    if (autLeload) {
        TIMER_CTL0(TIMER2) |= (uint32_t) TIMER_CTL0_ARSE;
    } else {
        TIMER_CTL0(TIMER2) &= ~(uint32_t) TIMER_CTL0_ARSE;
    }
    TIMER_DMAINTEN(TIMER2) |= ((uint32_t) TIMER_INT_UP);
    TIMER_CTL0(TIMER2) |= (uint32_t) TIMER_CTL0_CEN;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Timer 2 Init
 ---------------------------------------------------------------------------------------------------
 * @param : nonoe
 * 
 *@return : none 
 */
static void printhead_timer2_init() {

    timer_parameter_struct timer_basestructure;
    uint32_t system_clock = 0;
    uint32_t Timer2_prescaler = 0;

    if (48000000U == SystemCoreClock) {
        Timer2_prescaler = 3U;
    } else if (72000000U == SystemCoreClock) {
        Timer2_prescaler = 5U;
    } else if (96000000U == SystemCoreClock) {
        Timer2_prescaler = 7U;
    } else if (120000000U == SystemCoreClock) {
        Timer2_prescaler = 9U;
    } else {
        /*  reserved  */
    }

    system_clock = (SystemCoreClock / 1000000U);
    Timer_VALUE = (system_clock / (Timer2_prescaler + 1));
    /*Timer Config*/
    timer_basestructure.period = Timer_VALUE - 1;
    timer_basestructure.prescaler = Timer2_prescaler;
    timer_basestructure.alignedmode = TIMER_COUNTER_EDGE;
    timer_basestructure.counterdirection = TIMER_COUNTER_UP;
    timer_basestructure.clockdivision = TIMER_CKDIV_DIV1;
    timer_basestructure.repetitioncounter = 0U;

    /*Enable Clock*/
    rcu_periph_clock_enable(RCU_TIMER1);
    rcu_periph_clock_enable(RCU_TIMER2);



    nvic_irq_enable(TIMER1_IRQn, 0x01, 0x00);
    nvic_irq_enable(TIMER2_IRQn, 0x01, 0x01);

    /*Init Timer 1*/





    /*disable Timers*/
    TIMER_CTL0(TIMER1) &= ~(uint32_t) TIMER_CTL0_CEN;
    TIMER_CTL0(TIMER2) &= ~(uint32_t) TIMER_CTL0_CEN;


    /*Init Timers */
    timer_init(TIMER1, &timer_basestructure);
    timer_init(TIMER2, &timer_basestructure);

    TIMER_CTL0(TIMER1) &= ~(uint32_t) TIMER_CTL0_ARSE;
    TIMER_CTL0(TIMER2) &= ~(uint32_t) TIMER_CTL0_ARSE;

    /*Stop Intrrupt Of Timers*/
    TIMER_DMAINTEN(TIMER1) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_DMAINTEN(TIMER2) &= (~(uint32_t) TIMER_INT_UP);

    /*Clear Flag*/
    TIMER_INTF(TIMER1) = (~(uint32_t) TIMER_INT_UP);
    TIMER_INTF(TIMER2) = (~(uint32_t) TIMER_INT_UP);
}

static void Start_Heat_Timer() {
    /* TIMER2 interrupt Flag Clear */
    TIMER_INTF(TIMER1) = (~(uint32_t) TIMER_INT_UP);
    TIMER_DMAINTEN(TIMER1) |= ((uint32_t) TIMER_INT_UP);
    TIMER_CTL0(TIMER1) |= (uint32_t) TIMER_CTL0_CEN;
}

static void Stop_Heat_Timer() {
    /* TIMER2 interrupt Flag Clear */
    TIMER_DMAINTEN(TIMER1) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_INTF(TIMER1) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_CTL0(TIMER1) &= (~(uint32_t) TIMER_CTL0_CEN);
}

static void Stop_Stepper_Timer() {
    TIMER_DMAINTEN(TIMER2) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_INTF(TIMER2) &= (~(uint32_t) TIMER_INT_UP);
    TIMER_CTL0(TIMER2) &= (~(uint32_t) TIMER_CTL0_CEN);
}

static void SPI0_Init() {
    /*Enable SPI 2 Remap*/
    rcu_periph_clock_enable(RCU_SPI0);
    /*Enable SPI 2 Remap*/
    gpio_pin_remap_config(GPIO_SPI0_REMAP, ENABLE);
    gpio_pin_remap_config(GPIO_SWJ_DISABLE_REMAP, ENABLE);
    /*SPI0 GPIO config:MISCK/PB3*/
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, GPIO_PIN_3);
    /* SPI0 GPIO config:MOSI/PB5*/
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, GPIO_PIN_5);
    /* SPI2 parameter config */
    spi_parameter_struct spi_init_struct;
    spi_init_struct.trans_mode = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_4;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);
    spi_i2s_interrupt_disable(SPI0, SPI_I2S_INT_RBNE);
    spi_i2s_interrupt_disable(SPI0, SPI_I2S_INT_TBE);
    spi_enable(SPI0);
}

static uint16_t Size = 0;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Put Action In the QueueBuffer
 ---------------------------------------------------------------------------------------------------
 * @param :  max Dot Drawing in Ypos
 * 
 * @param : N Bit ImageNumber Or max char Drawing
 * 
 * @param :values is one from list {Feed , PrintData , Print Nv ,Print Download Images ,Cut}
 * 
 * @return : void
 *
 */
uint8_t PutAction(uint16_t MaxLine, uint8_t *buffer, uint16_t MaxDotPerLine, uint8_t justify, uint8_t Feed) {

    st_hardware_handel_drawing stHanelHardware;
    uint8_t *ptr;
    uint16_t i = 0;
    uint16_t Index = 0;
    uint16_t FreeStruct = 0;
    uint16_t maxByteInBuffer = 0;
    uint16_t startByte = 0;
    uint16_t NewY;
    FreeStruct = fifo_N_struct_free(&gstFifoAction);

    if (MaxLine > FreeStruct) {
        return (0);
    }

    gstPrintHead.NByte = (getMaxDotPerLine() >> 3);
    maxByteInBuffer = (MaxDotPerLine + 7) >> 3;

    if (getupSizeDown()) {
        gstPrintHead.headreverse = 1;
        SPI_CTL0(SPI0) |= (uint32_t) (SPI_CTL0_LF);
        gstPrintHead.Pre = 4;
        NewY = (getMaxLine());
    } else {
        NewY = (getMaxLine() - MaxLine);
        SPI_CTL0(SPI0) &= (uint32_t) (~SPI_CTL0_LF);
        gstPrintHead.Pre = 4;
        gstPrintHead.headreverse = 0;
    }
    gstPrintHead.Post = HEAD_NBYTE - (gstPrintHead.NByte + gstPrintHead.Pre);
    if (maxByteInBuffer != 0) {
        if (justify == 0x01) {
            startByte = (gstPrintHead.NByte - maxByteInBuffer) >> 1;
        } else if (justify == 0x02) {
            startByte = (gstPrintHead.NByte - maxByteInBuffer);
        } else {
            startByte = 0;
        }
    }
    i = 0;
    ptr = (uint8_t *) & buffer[NewY * (gstPrintHead.NByte)];
    setBuff(stHanelHardware.LineBuffer, 0x00, gstPrintHead.NByte);
    if (Feed == 0) {
        while (i < MaxLine) {
            (void) fifo_struct_write(&gstFifoAction, &stHanelHardware);
            i++;
        }
        return (1);
    }
    while (i < MaxLine) {
        Index = i * (gstPrintHead.NByte);
        copyBuff(stHanelHardware.LineBuffer + startByte, ptr + Index, gstPrintHead.NByte - startByte);
        (void) fifo_struct_write(&gstFifoAction, &stHanelHardware);
        setBuff(ptr + Index, 0x00, gstPrintHead.NByte);
        i++;
    }
    Size = MAX_VALUE(Size, fifo_N_struct_used(&gstFifoAction));
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Run Actions Values
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * @return : none
 *
 */
void RunActions() {

    if (getCutState() == 0) {
        return;
    }
    if (gstPrintHead.u8State == 0) {
        if (fifo_struct_Read(&gstFifoAction, &gstHardwareData) == FIFO_ERR_NO_DAT) {
            return;
        }
        GPIO_BOP(FEED_ENABLE_PORTx) = (uint32_t) FEED_ENABLE_PINx;
        GPIO_BOP(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;
        HeatLoad(gstPrintHead.setHeatTime);
        gstPrintHead.u8State = 1;
        printhead_write_Data();
        StepperLoad(1U, 0);
    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : check Action buffer is empty or not
 ---------------------------------------------------------------------------------------------------
 * @param :  none
 * 
 * 
 * @return : 0 is not empty , 1 is empty
 *
 */
uint8_t QueuLineEmpty() {
    if (fifo_N_struct_used(&gstFifoAction) == 0) {
        return (1);
    }
    return (0);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
void printhead_init(void) {
    printhead_timer2_init();
    printhead_pins_init();
    SPI0_Init();
    adc_config();
    setBuff(gu8MaxActions, 0x00, MAX_ACTION * sizeof (st_hardware_handel_drawing));
    fifo_struct_init(&gstFifoAction, gu8MaxActions, MAX_ACTION, sizeof (st_hardware_handel_drawing));
    setBuff(&gstPrintHead, 0x00, sizeof (st_printhead_t));

    gstPrintHead.speed = DEFAULT_SPEED;
    gstPrintHead.setHeatTime = DEFAULT_HEAT_TIME;
    gstPrintHead.stepRun = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : heat Time
 ---------------------------------------------------------------------------------------------------
 * @param : Time per us to heat
 * 
 * @return : none
 */
void Printer_Deneisty(uint16_t heatTime) {

    if (heatTime >= MAX_HEAT_TIME) {
        gstPrintHead.setHeatTime = MAX_HEAT_TIME;
        return;
    }
    if (heatTime <= MIN_HEAT_TIME) {
        gstPrintHead.setHeatTime = MIN_HEAT_TIME;
        return;
    }

    gstPrintHead.setHeatTime = heatTime;

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : speed between min and max speed
 * 
 * @return : none 
 */
void Printer_Speed(uint16_t speed) {
    if (speed >= MAX_SPEED) {
        gstPrintHead.speed = MAX_SPEED;
        return;
    }
    if (speed <= MIN_SPEED) {
        gstPrintHead.speed = MIN_SPEED;
        return;
    }
    gstPrintHead.speed = speed;
    gstPrintHead.stepTime = (micros_t) ((1000U * STEP_DISTANCE) / speed);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : return to default speed
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
void printhead_defaultSpeed() {
    gstPrintHead.speed = DEFAULT_SPEED;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : return to default speed
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
void printhead_defaultDenesity() {
    gstPrintHead.setHeatTime = DEFAULT_HEAT_TIME;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : spi transmit data 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
static void printhead_startHeat(void) {
    GPIO_BC(PRINTER_LAT_PORTx) = (uint32_t) PRINTER_LAT_PINx;
    GPIO_BOP(PRINTER_LAT_PORTx) = (uint32_t) PRINTER_LAT_PINx;
    GPIO_BOP(PRINTER_STB_PORTx) = (uint32_t) PRINTER_STB_PINx;
    Start_Heat_Timer();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : spi transmit data 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
static void printhead_write_Data(void) {
    /**/
    uint8_t i;
    if (gstPrintHead.headreverse == 0) {

        for (i = 0; i < gstPrintHead.Pre; i++) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));
            SPI_DATA(SPI0) = (uint32_t) 0x00;
        }

        for (i = 0; i < gstPrintHead.NByte; i++) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));
            SPI_DATA(SPI0) = (uint32_t) gstHardwareData.LineBuffer[i];
            gstHardwareData.LineBuffer[i] = 0x00;
        }
        for (i = 0; i < gstPrintHead.Post; i++) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));
            SPI_DATA(SPI0) = (uint32_t) 0x00;
        }

    } else {
        i = 0;

        for (i = 0; i < gstPrintHead.Pre; i++) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));

            SPI_DATA(SPI0) = (uint32_t) 0x00;
        }

        for (i = gstPrintHead.NByte; i != 0; i--) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));
            SPI_DATA(SPI0) = (uint32_t) gstHardwareData.LineBuffer[i - 1];
            gstHardwareData.LineBuffer[i] = 0;
        }
        for (i = 0; i < gstPrintHead.Post; i++) {
            while (!(SPI_STAT(SPI0) & SPI_FLAG_TBE));
            SPI_DATA(SPI0) = (uint32_t) 0x00;
        }

    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : print head is 
 ---------------------------------------------------------------------------------------------------
 * @param : LSB Bit is true or false
 * 
 * @param : max line copy
 * 
 * 
 * @return:none
 */
void printhead_LSB(uint8_t value) {
    gstPrintHead.headreverse = value & 0x01;

}

#if TESET_TIME

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : print head is 
 ---------------------------------------------------------------------------------------------------
 * @param : LSB Bit is true or false
 * 
 * @param : max line copy
 * 
 * 
 * @return:none
 */
void Print_Time() {

    for (uint8_t i = 0; i < 30; i++) {
        printu32Number(timebuffer[i]);
        PrintChar(' ');
    }
    PrintChar(0x0A);
    PrintChar('M');
    PrintChar('A');
    PrintChar('X');
    PrintChar(':');
    printu32Number(maxTime);
    PrintChar(0x0A);
    PrintChar('M');
    PrintChar('I');
    PrintChar('N');
    PrintChar(':');
    printu32Number(minTime);
    PrintChar(0x0A);
}
#endif

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
static void adc_config() {
    /* enable ADC1 clock */
    rcu_periph_clock_enable(RCU_ADC0);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);
    /* config ADC clock */
    gpio_init(ADC_GPIO_PORT, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, ADC_GPIO_PIN);
    /* ADC mode config */
    ADC_CTL0(ADC0) &= ~(ADC_CTL0_SYNCM);
    ADC_CTL0(ADC0) |= ADC_MODE_FREE;
    /* ADC data alignment config */
    ADC_CTL1(ADC0) &= ~((uint32_t) ADC_CTL1_DAL);
    /* ADC channel length config */
    ADC_RSQ0(ADC0) &= ~((uint32_t) ADC_RSQ0_RL);
    ADC_RSQ0(ADC0) |= RSQ0_RL((uint32_t) (0));
    /* ADC trigger config */
    ADC_CTL1(ADC0) &= ~((uint32_t) ADC_CTL1_ETSRC);
    ADC_CTL1(ADC0) |= (uint32_t) ADC0_1_2_EXTTRIG_REGULAR_NONE;
    /* ADC external trigger config */
    ADC_CTL1(ADC0) |= ADC_CTL1_ETERC;


    ADC_RSQ2(ADC0) &= ~((uint32_t) (ADC_RSQX_RSQN));
    ADC_RSQ2(ADC0) |= ((uint32_t) ADC_CHANNEL_3);


    ADC_SAMPT1(ADC0) &= ~((uint32_t) (ADC_SAMPTX_SPTN << (3U * ADC_CHANNEL_3)));
    ADC_SAMPT1(ADC0) |= (uint32_t) (ADC_SAMPLETIME_1POINT5 << (3U * ADC_CHANNEL_3));

    ADC_OVSAMPCTL(ADC0) &= ~((uint32_t) ADC_OVSAMPCTL_DRES);
    ADC_OVSAMPCTL(ADC0) |= (uint32_t) ADC_RESOLUTION_10B;
    /* enable ADC interface */
    ADC_CTL1(ADC0) |= (uint32_t) ADC_CTL1_ADCON;
    __delay_ms(1U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
static inline void adcEnable() {
    /*Software Enable */
    ADC_CTL1(ADC0) |= (uint32_t) ADC_CTL1_ADCON;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
static inline void adcDisable() {
    ADC_CTL1(ADC0) &= ~(uint32_t) ADC_CTL1_ADCON;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init value of the Print Head
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
static inline uint16_t adcReadData() {
    /* ADC regular channel config */
    ADC_CTL1(ADC0) |= ADC_CTL1_SWRCST;
    /* wait the end of conversion flag */
    while (!(ADC_STAT(ADC0) & ADC_FLAG_EOC));
    /* clear the end of conversion flag */
    ADC_STAT(ADC0) = ~((uint32_t) ADC_FLAG_EOC);
    /* return regular channel sample value */
    return (uint16_t) (ADC_RDATA(ADC0));
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Reset Cut
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none 
 */
void ResetHead() {
    Stop_Heat_Timer();
    Stop_Stepper_Timer();
    gstPrintHead.stepRun = 0;
    gsStepCounter = 0;
    gstPrintHead.u8State = 0;
    GPIO_BC(FEED_ENABLE_PORTx) = (uint32_t) FEED_ENABLE_PINx;
    GPIO_BC(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;
}

uint16_t PrintSpeed() {
    return gstPrintHead.speed;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Pinter Temp
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : Temp
 */
uint8_t ShowCurrentTemp() {
    return (gu8Tempp[adcReadData()]);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Enable Power Pin
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : Temp
 */
void EnablePowerPin() {
    GPIO_BOP(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Disable Power Pin
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : Temp
 */
void DisablePowerPin() {
    GPIO_BC(PRINTER_POWER_SW_PORTx) = (uint32_t) PRINTER_POWER_SW_PINx;
}

void PritMAxSize() {
    printu16Number(Size);
    PrintChar(0x0A);
}