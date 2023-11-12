/*
 ---------------------------------------------------------------------------------------------------
 * @brief : FEED BUTTON
 ---------------------------------------------------------------------------------------------------
 */

#include <AllFilesInc.h>
#include <stdint-gcc.h>
#include <stddef.h>
#define  FEED_PORTx            GPIOC   
#define  FEED_PINx             GPIO_PIN_6
#define  MAX_VALUE_READ           1
#define  BUTTON_MAX_BIT_OF_CODE        BUTTON_MAX_EVENT
#define bitSet8Bit(value, bit) ((value) |= (0x01 << (bit)))
#define bitClear8Bit(value, bit) ((value) &=  ~(0x01 << (bit)))

#define FEED_RESELASE        RESET
#define FEED_PRESS           SET

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef union {
    uint8_t Flags;

    struct {
        unsigned TabCounter : 4;
        unsigned LongTabFlag : 1;
        unsigned NewCallBackHandle : 1;
        unsigned MultiTabFlag : 1;
    };
} ukeyStates_t;

typedef struct {
    uint8_t FeedCounter;
    uint8_t StateValue;
    uint8_t buttonValue;
    uint8_t KeyCode;
    uint8_t current;
    uint8_t last;
    uint8_t beforeLast;
    pFunckeyEvent_t gpFunKeyScan;
    stkey_t gKeyEventQueue[4];
    stStructFIFO_t gstButton;
} st_feedbutton_t;

/*
 * <@var gstKeyLongPreeTimeOut           : Check Long Press TimeOut Or Not          
 */
static stTimer_TimeOut_t gstKeyLongPreeTimeOut;
/*
 * < @var gstKeyMutiTabTimeOut           :Check Multi Tab Time out    
 */
static stTimer_TimeOut_t gstKeyMultiTabTimeOut;
/*
 * <@var guKeypadFlags                  : Number of Keypad used 
 */
static ukeyStates_t guKeypadFlags;
/*
 * <@var guKeypadFlags                  : Number of Keypad used 
 */
static st_feedbutton_t gsFeedButton;
/*
 * <@var gpcKeyEvents                  : Pointer to const Key Events
 */
static stkey_t gGetKey;

static void PutIntoQueue(void);
static void GetFromQueue();

void FeedButtonInit() {
    gpio_init(FEED_PORTx, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_MAX, FEED_PINx);
    fifo_struct_init(&gsFeedButton.gstButton, gsFeedButton.gKeyEventQueue, 4, sizeof (stkey_t));
    gsFeedButton.FeedCounter = 0;
    gsFeedButton.StateValue = 0;
    gsFeedButton.buttonValue = SET;
    gsFeedButton.KeyCode = SET;
    gsFeedButton.current = RESET;
    gsFeedButton.gpFunKeyScan = NULL;
    gsFeedButton.beforeLast = RESET;
    gsFeedButton.last = RESET;
    gGetKey.State = CANCELED;
    gGetKey.TabCounter = 0;
    guKeypadFlags.Flags = 0x00;
    guKeypadFlags.MultiTabFlag = 0;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Feed Button Scan >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FeedButtonScan                                                                |  
 | < @Description       : scan feed button                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FeedButtonScan() {
    if (gsFeedButton.StateValue == 0) {
        gsFeedButton.FeedCounter = DEPOUND_TIME;
        gsFeedButton.buttonValue = gpio_input_bit_get(FEED_PORTx, FEED_PINx);
        gsFeedButton.StateValue = 1;
        return;
    }

    if (gsFeedButton.StateValue == 1) {
        if (gsFeedButton.buttonValue != gpio_input_bit_get(FEED_PORTx, FEED_PINx)) {
            gsFeedButton.StateValue = 0;
            return;
        }

        if (gsFeedButton.FeedCounter != 0) {
            gsFeedButton.FeedCounter--;
            return;
        }
        gsFeedButton.KeyCode = gsFeedButton.buttonValue;
        gsFeedButton.StateValue = 0;

    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadRegisterEvent >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadRegisterEvent                                                       |  
 | < @Description       : register call back function into Array                                         | 
 | < @Param callback    : callback Function                                                              |
 | < @Param Index       : Event Index                                                                    | 
 * < @Param Tab         : 1 key has work multi tab else key work with no mutitab
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonRegisterEvent(pFunckeyEvent_t callback) {
    gsFeedButton.gpFunKeyScan = callback;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadResetTabCounter >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadResetTabCounter                                                     |  
 | < @Description       : Reset Tab Counter                                                              | 
 | < @Param key         : pointer to assignment key                                                      |                                                   |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonResetTabCounter(stkey_t *key, uint8_t Tab) {
    key->TabCounter = 0;
    guKeypadFlags.MultiTabFlag = Tab;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadGetFromQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void GetFromQueue(void) {
    if (guKeypadFlags.NewCallBackHandle == 0) {
        if (fifo_struct_Read(&gsFeedButton.gstButton, &gGetKey) == FIFO_ERR_NO_DAT) {
            return;
        }

        if (gsFeedButton.gpFunKeyScan != NULL) {
            /*tone Generation*/
            guKeypadFlags.NewCallBackHandle = 1;
            return;
        }
        return;
    }
    if (gsFeedButton.gpFunKeyScan(&gGetKey)) {
        guKeypadFlags.NewCallBackHandle = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadQueueKey >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key and Put into Queue                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void PutIntoQueue(void) {

    stkey_t key;

    if (gsFeedButton.current == gsFeedButton.KeyCode) {
        /*same key check long press time out */
        if ((guKeypadFlags.LongTabFlag)) {
            /*Long Tab is Done */
            if ((sysIsTimeoutMs(&gstKeyLongPreeTimeOut) == true)) {
                sysSetPeriodMS(&gstKeyLongPreeTimeOut, 5); /*active Long Press Time*/
                key.State = LONG_TAP;
                fifo_struct_write(&gsFeedButton.gstButton, &key);
                return;
            }
            return;
        }
        return;
    }

    /*assignment a new Key*/
    gsFeedButton.beforeLast = gsFeedButton.last;
    gsFeedButton.last = gsFeedButton.current;
    gsFeedButton.current = gsFeedButton.KeyCode;


    if (gsFeedButton.current == FEED_RESELASE) {
        guKeypadFlags.LongTabFlag = 0;
        key.State = KEY_RELEASE;
        fifo_struct_write(&gsFeedButton.gstButton, &key);
        return;
    }


    if (gsFeedButton.current == FEED_PRESS && gsFeedButton.last == FEED_RESELASE) {
        guKeypadFlags.LongTabFlag = 1; /*long Press is OK*/
        sysSetPeriodMS(&gstKeyLongPreeTimeOut, LONG_TIME); /*active Long Press Time*/
        if ((gsFeedButton.beforeLast == FEED_PRESS) && (!guKeypadFlags.MultiTabFlag)) {
            guKeypadFlags.TabCounter++;
            if (sysIsTimeoutMs(&gstKeyMultiTabTimeOut) == true) {
                key.TabCounter = guKeypadFlags.TabCounter;
                key.State = MULTI_TAP;
                guKeypadFlags.TabCounter = 0;
                fifo_struct_write(&gsFeedButton.gstButton, &key);
            }
            
        } else {
            guKeypadFlags.TabCounter = 0;
            key.TabCounter = 0;
            guKeypadFlags.MultiTabFlag = 0;
            key.State = KEY_PRESS;
            fifo_struct_write(&gsFeedButton.gstButton, &key);
        }
        sysSetPeriodMS(&gstKeyMultiTabTimeOut, MUTI_TIME_OUT);
        return;
    }
    guKeypadFlags.TabCounter = 0;
    guKeypadFlags.LongTabFlag = 0;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in background                                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ButtonDriver() {
    PutIntoQueue();
    GetFromQueue();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in background                                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void LongNoReapt() {
    guKeypadFlags.LongTabFlag = 0;
}