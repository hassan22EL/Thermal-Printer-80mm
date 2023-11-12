
#include <AllFilesInc.h>
#include <stdbool.h>

#include "cutOperation.h"
/*
 ---------------------------------------------------------------------------------------------------
 * @brief : Cut Pin Assignment
 ---------------------------------------------------------------------------------------------------
 */


#define CUT_TIME_OUT              3000U
#define CUT_INPUT_PORTx           GPIOC
#define CUT_INPUT01_PINx          GPIO_PIN_2
#define CUT_INPUT02_PINx          GPIO_PIN_3

#define CUT_KEY1_PIN                    GPIO_PIN_9
#define CUT_KEY1_GPIO_PORT              GPIOB
#define CUT_KEY1_GPIO_CLK               RCU_GPIOB
#define CUT_KEY1_EXTI_LINE              EXTI_9
#define CUT_KEY1_EXTI_PORT_SOURCE       GPIO_PORT_SOURCE_GPIOB
#define CUT_KEY1_EXTI_PIN_SOURCE        GPIO_PIN_SOURCE_9
#define CUT_KEY1_EXTI_IRQn              EXTI5_9_IRQn

typedef enum {
    OFF = 0,
    REVERSE = 1,
    FORWARD = 2,
    BREAK = 3,
} en_CutMotorState_t;

typedef struct {
    uint8_t u8UserState;
    uint8_t u8CutterError;
} st_motor_flags_t;

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : State Var
 ---------------------------------------------------------------------------------------------------
 */
static st_motor_flags_t gstMotorSwitch;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : TomeOut
 ---------------------------------------------------------------------------------------------------
 */
static stTimer_TimeOut_t gstCutterTimeOut;
/*
 ---------------------------------------------------------------------------------------------------
 * @brief :  Internal Function ProtoType
 ---------------------------------------------------------------------------------------------------
 */

static void EnableSwitchInterrupt(exti_trig_type_enum type);
static void MotorStartOperation(en_CutMotorState_t Value);
static void DisableSwitchInterrupt();

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Init all I/O Pins in this Driver
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
void cut_Init(void) {
    rcu_periph_clock_enable(CUT_KEY1_GPIO_CLK);
    gpio_init(CUT_INPUT_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, CUT_INPUT01_PINx);
    gpio_init(CUT_INPUT_PORTx, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, CUT_INPUT02_PINx);
    gpio_init(CUT_KEY1_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_MAX, CUT_KEY1_PIN);
    /* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(CUT_KEY1_EXTI_IRQn, 0x00, 0x00);
    DisableSwitchInterrupt();
    gstMotorSwitch.u8UserState = 4;

    gstMotorSwitch.u8CutterError = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Reset Cut Operation
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
void ResetCut() {
    DisableSwitchInterrupt();
    gstMotorSwitch.u8UserState = 4;
    gstMotorSwitch.u8CutterError = 0;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cut Operation 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
void CutNow() {
    EnablePowerPin();
    MotorStartOperation(REVERSE);
    EnableSwitchInterrupt(EXTI_TRIG_FALLING);
    sysSetPeriodMS(&gstCutterTimeOut, CUT_TIME_OUT);
    gstMotorSwitch.u8UserState = 1;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : get cutter Error State
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : 0 is no Have error , 1 system have error 
 */
uint8_t CutErrorState() {
    return gstMotorSwitch.u8CutterError;
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : Motor State
 ---------------------------------------------------------------------------------------------------
 * @param : Motor State Value {OFF , REVERSE , FORWARD, BREAK}
 * 
 *@return : none 
 */
static void MotorStartOperation(en_CutMotorState_t Value) {
    bit_status Pin1 = (Value & (0x01 << 1)) ? SET : RESET;
    bit_status Pin2 = (Value & (0x01 << 0)) ? SET : RESET;
    gpio_bit_write(CUT_INPUT_PORTx, CUT_INPUT01_PINx, Pin1);
    gpio_bit_write(CUT_INPUT_PORTx, CUT_INPUT02_PINx, Pin2);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cut Operation 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
void Cutter() {
    switch (gstMotorSwitch.u8UserState) {
        case 0:
            break;
        case 1:/*Power On*/
            if (sysIsTimeoutMs(&gstCutterTimeOut) == true) {
                /*the fail edge not detect Go to 2*/
                EnableSwitchInterrupt(EXTI_TRIG_FALLING);
                MotorStartOperation(REVERSE);
                sysSetPeriodMS(&gstCutterTimeOut, CUT_TIME_OUT);
                gstMotorSwitch.u8UserState = 2;
            }
            break;
        case 2:
            if (sysIsTimeoutMs(&gstCutterTimeOut) == true) {
                MotorStartOperation(OFF);
                gstMotorSwitch.u8UserState = 0;
                DisableSwitchInterrupt();
                gstMotorSwitch.u8CutterError = 1;


            }
            break;
        case 3:
            if (sysIsTimeoutMs(&gstCutterTimeOut) == true) {
                gstMotorSwitch.u8UserState = 4; /*check the motor state*/
                gstMotorSwitch.u8CutterError = 0;
                MotorStartOperation(OFF);

            }
            break;
        case 4:
            if (gpio_input_bit_get(CUT_KEY1_GPIO_PORT, CUT_KEY1_PIN) != RESET) {
                EnablePowerPin();
                EnableSwitchInterrupt(EXTI_TRIG_FALLING);
                MotorStartOperation(REVERSE);
                sysSetPeriodMS(&gstCutterTimeOut, CUT_TIME_OUT);
                gstMotorSwitch.u8CutterError = 0;
                gstMotorSwitch.u8UserState = 2;
                return;
            }
            DisablePowerPin();
            gstMotorSwitch.u8UserState = 0;
            break;
        default:
            gstMotorSwitch.u8UserState = 0;
            break;

    }
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cut Operation 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
uint8_t getCutState() {
    if (gstMotorSwitch.u8UserState != 0) {
        return (0);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cut Operation 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
static void EnableSwitchInterrupt(exti_trig_type_enum type) {

    /* connect key EXTI line to key GPIO pin */
    gpio_exti_source_select(CUT_KEY1_EXTI_PORT_SOURCE, CUT_KEY1_EXTI_PIN_SOURCE);
    /* configure key EXTI line */
    exti_init(CUT_KEY1_EXTI_LINE, EXTI_INTERRUPT, type);
    exti_interrupt_flag_clear(CUT_KEY1_EXTI_LINE);
    exti_interrupt_enable(CUT_KEY1_EXTI_LINE);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cut Operation 
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
static void DisableSwitchInterrupt() {
    exti_init(CUT_KEY1_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_NONE);
    exti_interrupt_flag_clear(CUT_KEY1_EXTI_LINE);
    exti_interrupt_disable(CUT_KEY1_EXTI_LINE);
}

/*
 ---------------------------------------------------------------------------------------------------
 * @brief  : cutter-Operation in isr
 ---------------------------------------------------------------------------------------------------
 * @param : none
 * 
 *@return : none 
 */
void cutter_isr(void) {
    MotorStartOperation(BREAK);
    DisableSwitchInterrupt();
    gstMotorSwitch.u8UserState = 3;
    sysSetPeriodMS(&gstCutterTimeOut, 100);
}