/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : Tone.h                                                                   |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 11 Byte Used by one Pin                                                  |
| < PROGRAM USAGE            : 430 Byte by One Pin Used                                                 |                                                                         |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#include <AllFilesInc.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cutOperation.h"

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Micros of Status
 ---------------------------------------------------------------------------------------------------
 */
typedef union {
    uint32_t state;

    struct {
        unsigned ToneState : 2;
        unsigned CutStatusState : 1;
        unsigned flashUserState : 2;
    };


} ut_ButtonState_t;



/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Buzzer 
 ---------------------------------------------------------------------------------------------------
 */
#define  BUZ_PORTx        GPIOA
#define  BUZ_PINx        GPIO_PIN_8
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Power LED
 ---------------------------------------------------------------------------------------------------
 */

#define  POWER_PORTx         GPIOC
#define  POWER_PINx          GPIO_PIN_8

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : ERROR LED
 ---------------------------------------------------------------------------------------------------
 */
#define  ERROR_PORTx         GPIOB
#define  ERROR_PINx          GPIO_PIN_15

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : PAPER LED
 ---------------------------------------------------------------------------------------------------
 */
#define  PAPER_PORTx          GPIOC
#define  PAPER_PINx          GPIO_PIN_7

/*
 ---------------------------------------------------------------------------------------------------
 * @brief : PAPER_SENSOR
 ---------------------------------------------------------------------------------------------------
 */
#define  PAPER_SENSOR_PORTx                  GPIOA  
#define  PAPER_SENSOR_PINx                   GPIO_PIN_0
#define  PAPER_SENSOR_DRIVE_PORTx            GPIOB
#define  PAPER_SENSOR_DRIVE_PINx             GPIO_PIN_8
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : DOOR 
 ---------------------------------------------------------------------------------------------------
 */
#define DOOR_PORTX   GPIOC
#define DOOR_PINx    GPIO_PIN_9

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef struct {
    stTimer_TimeOut_t Freq;
    uint32_t duration;
    uint32_t Period[2];
    uint8_t toggle;
    uint8_t State;
} stTone_t;

typedef struct {
    ut_ButtonState_t gutFeedButton;
    uint8_t gu8ToneCounter;

} st_user_state_t;

/*
 *<@var gstTones : max tones used in system
 */
static stTone_t gstTones;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  flash memory user state
 ---------------------------------------------------------------------------------------------------
 */
static st_user_state_t gstUserState;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  current Tone state
 ---------------------------------------------------------------------------------------------------
 */
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Proto Type Functions >                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
static void myStatus(uint32_t port, uint32_t pin, bit_status defalutstate, stTone_t *tone);
static void BuzzerOnPeriod();

static void CutStatus();
static void flash_error_status();
static uint8_t isStatusPlaying();
static void StatusPlay(uint32_t Period, uint32_t duration, uint32_t Ton);
static void StatusStop(uint32_t port, uint32_t pin, bit_status defaultState);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < myTone >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t myTone                                                                 |  
 | < @Description       : run Timer                                                                      |                                               |
 | < @return            :void                                                   |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void myStatus(uint32_t port, uint32_t pin, bit_status defalutstate, stTone_t *tone) {
    static uint8_t toggle;
    if (!tone->State) {
        return;
    }
    if (sysIsTimeoutUs(&tone->Freq) == true) {
        if (tone->toggle == 0) {
            if (tone->duration == 0) {
                tone->State = 0;
                tone->toggle = 0;
                if (defalutstate) {
                    GPIO_BOP(port) = (uint32_t) pin;
                } else {
                    GPIO_BC(port) = (uint32_t) pin;
                }
                return;
            }
            tone->duration--;
        }

        sysSetPeriodUS(&tone->Freq, tone->Period[tone->toggle]);
        tone->toggle ^= 1;
        if (tone->Period[0] != 0) {
            if (toggle) {
                GPIO_BOP(port) = (uint32_t) pin;
            } else {
                GPIO_BC(port) = (uint32_t) pin;
            }

            toggle ^= 1;
        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < isTonePlaying >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : check the Tone is Playing or not                                               |   
 | < @Param Index       : Signal Index in array                                                          |
 | < @return            : 1 is Playing , 0 is not Playing                                                |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t isStatusPlaying() {
    return gstTones.State;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Toneplay >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void Toneplay                                                                  |  
 | < @Description       : Play Tone                                                                      | 
 | < @Param Pin         : GPIO Pin access                                                                |
 | < @Param Period      : Period gnerated                                                                |  
 | < @Param duration    : time to generate this Frequncy                                                 |
 | < @Param Index       : Index of the Pin From 0 to max pin used -1                                     |
 | <@Param Ton          : Time of on                                                                    |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void StatusPlay(uint32_t Period, uint32_t duration, uint32_t Ton) {
    gstTones.Period[0] = Ton;
    gstTones.Period[1] = Period - Ton;
    gstTones.State = 1;
    gstTones.duration = duration;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Tonestop >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : stop this tone                                                                 |  
 | < @Param pin         : access gpio pin                                                                |
 | < @Param  Index      : Signel Index in array                                                          |
 | < @param default     : state low or high                                                              |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void StatusStop(uint32_t port, uint32_t pin, bit_status defaultState) {
    gstTones.State = 0;
    gpio_bit_write(port, pin, defaultState);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneInit >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneInit                                                                  |  
 | < @Description       : Init I/O with MAX_PIN Used                                                     |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void UserStatusInit() {

    /*Buz Init*/
    gpio_init(BUZ_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, BUZ_PINx);
    StatusStop(BUZ_PORTx, BUZ_PINx, RESET);

    /*Power Init*/
    gpio_init(POWER_PORTx, GPIO_MODE_OUT_OD, GPIO_OSPEED_MAX, POWER_PINx);
    gpio_bit_reset(POWER_PORTx, POWER_PINx);

    gpio_init(ERROR_PORTx, GPIO_MODE_OUT_OD, GPIO_OSPEED_MAX, ERROR_PINx);
    gpio_bit_set(ERROR_PORTx, ERROR_PINx);

    gpio_init(PAPER_PORTx, GPIO_MODE_OUT_OD, GPIO_OSPEED_MAX, PAPER_PINx);
    gpio_bit_set(PAPER_PORTx, PAPER_PINx);
    /*Paper Sensor Driver*/
    gpio_init(PAPER_SENSOR_DRIVE_PORTx, GPIO_MODE_OUT_OD, GPIO_OSPEED_MAX, PAPER_SENSOR_DRIVE_PINx);
    gpio_bit_set(PAPER_SENSOR_DRIVE_PORTx, PAPER_SENSOR_DRIVE_PINx);

    /*Feed*/

    /*Paper Sensor*/
    gpio_init(PAPER_SENSOR_PORTx, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, PAPER_SENSOR_PINx);
    /*Door*/
    gpio_init(DOOR_PORTX, GPIO_MODE_IPD, GPIO_OSPEED_MAX, DOOR_PINx);
    /*sensor Enable*/
    gpio_bit_reset(PAPER_SENSOR_DRIVE_PORTx, PAPER_SENSOR_DRIVE_PINx);
    gstUserState.gutFeedButton.state = 0; /**/

    gstTones.State = 0;
    gstTones.Period[0] = 0;
    gstTones.Period[1] = 0;
    gstUserState.gu8ToneCounter = 0;
    gstUserState.gutFeedButton.ToneState = 0;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneDriver >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneDriver                                                                |  
 | < @Description       : run in background task                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void UserStatusDriver() {
    myStatus(BUZ_PORTx, BUZ_PINx, RESET, &gstTones);
    BuzzerOnPeriod();
    checkSystemValid();
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : check Parper Sencor
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return : none
 */
void checkSystemValid() {
    /*bit Write The */
    if ((GPIO_ISTAT(DOOR_PORTX)&(DOOR_PINx)) != RESET) {
        setNumberOfTone(5);
        SystemGenerateError();
        GPIO_BC(PAPER_PORTx) = (uint32_t) (PAPER_PINx);

        GPIO_BC(ERROR_PORTx) = (uint32_t) (ERROR_PINx);
        return;
    }


    /*active scan */
    if ((GPIO_ISTAT(PAPER_SENSOR_PORTx)& (PAPER_SENSOR_PINx)) != RESET) {
        setNumberOfTone(3);
        SystemGenerateError();
        GPIO_BC(ERROR_PORTx) = (uint32_t) (ERROR_PINx);
        GPIO_BC(PAPER_PORTx) = (uint32_t) (PAPER_PINx);
        return;
    }
    /*cutter state*/
    if (CutErrorState()) {
        GPIO_BOP(PAPER_PORTx) = (uint32_t) (PAPER_PINx);
        SystemGenerateError();
        CutStatus();
        return;
    }
    if (gstUserState.gutFeedButton.flashUserState) {
        flash_error_status();
        SystemGenerateError();
        return;
    }

    SystemClearError();
    GPIO_BOP(PAPER_PORTx) = (uint32_t) (PAPER_PINx);
    GPIO_BOP(ERROR_PORTx) = (uint32_t) (ERROR_PINx);

}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  buzzer On Period State
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
static void BuzzerOnPeriod() {
    if (isStatusPlaying()) {
        return;
    }
    switch (gstUserState.gutFeedButton.ToneState) {
        case 0:
            break;
        case 1:
            if (gstUserState.gu8ToneCounter == 0) {
                StatusPlay(250, 3000, 0);
                gstUserState.gutFeedButton.ToneState = 3;
                return;
            }
            StatusPlay(250, 400, 250);
            gstUserState.gutFeedButton.ToneState = 2;
            break;
        case 2:
            StatusPlay(250, 400, 0);
            gstUserState.gutFeedButton.ToneState = 1;
            gstUserState.gu8ToneCounter--;
            break;
        case 3:
            /*stop Tone */
            gstUserState.gutFeedButton.ToneState = 0;
            break;
        default:
            gstUserState.gutFeedButton.ToneState = 0;
            break;

    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  number of tone Generate
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void setNumberOfTone(uint8_t MaxTone) {
    if (gstUserState.gutFeedButton.ToneState == 0) {
        gstUserState.gutFeedButton.ToneState = 1;
        gstUserState.gu8ToneCounter = MaxTone;
    }
}

/*
   ---------------------------------------------------------------------------------------------------
 * @brief :  Cut Status Error
   ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
static void CutStatus() {


    if (isStatusPlaying()) {
        return;
    }


    if (gstUserState.gutFeedButton.CutStatusState == 0) {
        StatusPlay(250, 4000, 250);
        GPIO_BC(ERROR_PORTx) = (uint32_t) (ERROR_PINx);
        gstUserState.gutFeedButton.CutStatusState = 1;
        return;
    }

    if (gstUserState.gutFeedButton.CutStatusState == 1) {
        StatusPlay(250, 4000, 0);
        GPIO_BOP(ERROR_PORTx) = (uint32_t) (ERROR_PINx);
        gstUserState.gutFeedButton.CutStatusState = 0;
        return;
    }

}

/*
   ---------------------------------------------------------------------------------------------------
 * @brief :  flash memory state
   ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: 0 flash memory have state , 1 flash memory not have state
 */
static void flash_error_status() {
    if (gstUserState.gutFeedButton.flashUserState == 1) {
        StatusPlay(250, 4000, 250);
        GPIO_BC(ERROR_PORTx) = (uint32_t) (ERROR_PINx);
        gstUserState.gutFeedButton.flashUserState = 2;
    } else if (gstUserState.gutFeedButton.flashUserState == 2) {
        if (isStatusPlaying() == 0) {
            gstUserState.gutFeedButton.flashUserState = 0;
        }
    } else {
        gstUserState.gutFeedButton.flashUserState = 0;
    }
}

/*
   ---------------------------------------------------------------------------------------------------
 * @brief :  flash run error 
   ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: none
 */
void run_flash_error() {
    gstUserState.gutFeedButton.flashUserState = 1;
}

/*
   ---------------------------------------------------------------------------------------------------
 * @brief :  get Door State 
   ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: SET , RESET
 */
uint8_t GetStateOfDoor() {
    if ((GPIO_ISTAT(DOOR_PORTX)&(DOOR_PINx)) != RESET) {
        return (1);
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
uint8_t PowerOffState() {
    if (isStatusPlaying()) {
        return (0);
    }

    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Read Current Data
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 * @return: void
 */
void PowerOnState() {
    StatusPlay(250, 4000, 250);
}