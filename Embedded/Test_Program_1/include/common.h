#ifndef COMMON_H_GUARD
#define COMMON_H_GUARD

#include <stdio.h>
#include <limits.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"

#include "mqtt_client.h"

#include "pinDefs.h"


#include <stdbool.h>

#define DEFAULT_VREF 1100

#define SERVO_MIN_DEGREES 0
#define SERVO_MAX_DEGREES 180

#endif