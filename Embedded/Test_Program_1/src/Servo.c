#include "common.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define SERVO_MAX_PULSE_LENGTH 2000
#define SERVO_MIN_PULSE_LENGTH 1000

const char * LOG_SERVO = "SERVO";

uint32_t servoDegreesToPulseLength( uint32_t degrees ) {
    // A linear mapping of degrees to pulse lengths
    return ( ( SERVO_MAX_PULSE_LENGTH - SERVO_MIN_PULSE_LENGTH ) * ( degrees - SERVO_MIN_DEGREES ) ) / ( SERVO_MAX_DEGREES - SERVO_MIN_DEGREES ) + SERVO_MIN_PULSE_LENGTH;
}

void servoInit( void ) {
    ESP_LOGI( LOG_SERVO, "initializing mcpwm servo control" );
    ESP_ERROR_CHECK( mcpwm_gpio_init( SERVO_MCPWM_UNIT, SERVO_MCPWM_PIN, PIN_SERVO ) );

    mcpwm_config_t pwmConfig;
    pwmConfig.frequency = 50;    // frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwmConfig.cmpr_a = 0;    // duty cycle of PWMxA = 0
    pwmConfig.cmpr_b = 0;    // duty cycle of PWMxb = 0
    pwmConfig.counter_mode = MCPWM_UP_COUNTER;
    pwmConfig.duty_mode = MCPWM_DUTY_MODE_0;
    ESP_ERROR_CHECK( mcpwm_init( SERVO_MCPWM_UNIT, MCPWM_TIMER_0, &pwmConfig) );    //Configure PWM0A & PWM0B with above settings

    ESP_ERROR_CHECK( mcpwm_set_duty_in_us( SERVO_MCPWM_UNIT, SERVO_MCPWM_TIMER, SERVO_MCPWM_GEN, servoDegreesToPulseLength( SERVO_MIN_DEGREES ) ) );
}

void servoSetAngle( uint32_t degrees ) {
    ESP_LOGI( LOG_SERVO, "Command to set servo to %d degrees", degrees );
    uint32_t pulseLength = servoDegreesToPulseLength( degrees );
    ESP_LOGI( LOG_SERVO, "Pulse length %d", pulseLength );
    ESP_ERROR_CHECK( mcpwm_set_duty_in_us( SERVO_MCPWM_UNIT, SERVO_MCPWM_TIMER, SERVO_MCPWM_GEN, pulseLength ) );
}

