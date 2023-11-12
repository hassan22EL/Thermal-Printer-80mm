/* 
 * File:   Feedbutton.h
 * Author: hassa
 *
 * Created on October 24, 2023, 7:40 PM
 */

#ifndef FEEDBUTTON_H
#define	FEEDBUTTON_H

#define  DEPOUND_TIME            10
#define  LONG_TIME               500
#define  MUTI_TIME_OUT           500

typedef enum KEY_STATE {
    KEY_PRESS = 0,
    MULTI_TAP = 1,
    LONG_TAP = 2,
    MULTI_KEY_PRESS = 3,
    KEY_RELEASE = 4,
    CANCELED = 5
} KEYSTATE_t;

typedef struct {
    uint8_t State;
    uint8_t TabCounter;
} stkey_t;

/*
 *Key Call back
 */
typedef uint8_t(*pFunckeyEvent_t)(stkey_t *key);

#define MAX_EVEVENT              (4)

#define  NO_KEY                (0x80) 




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
void buttonRegisterEvent(pFunckeyEvent_t callback);

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
void buttonResetTabCounter(stkey_t *key, uint8_t Tab);



void FeedButtonInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Feed Button Scan >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FeedButtonScan                                                                |  
 | < @Description       : scan feed button                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FeedButtonScan();

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in background                                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ButtonDriver();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in background                                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void LongNoReapt();

#endif	/* FEEDBUTTON_H */

