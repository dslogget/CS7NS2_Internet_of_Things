#ifndef PIN_DEFS_H_GUARD
#define PIN_DEFS_H_GUARD
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define PIN_LED GPIO_NUM_4
#define PIN_ACTIVEBUZZER GPIO_NUM_5
#define PIN_MICROPHONE GPIO_NUM_17
#define PIN_PIR GPIO_NUM_18

#define PIN_ULTRA_TRIG GPIO_NUM_19
#define PIN_ULTRA_ECHO GPIO_NUM_21

#define PIN_SERVO GPIO_NUM_16
#define SERVO_MCPWM_UNIT MCPWM_UNIT_0
#define SERVO_MCPWM_PIN MCPWM0A
#define SERVO_MCPWM_GEN MCPWM_GEN_A
#define SERVO_MCPWM_TIMER MCPWM_TIMER_0

#define CHANNEL_LDR ADC_CHANNEL_7
#define CHANNEL_WATER ADC_CHANNEL_6


#endif
