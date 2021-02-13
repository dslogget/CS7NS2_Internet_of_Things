#ifndef COMMON_H_GUARD
#define COMMON_H_GUARD

#include <stdio.h>
#include <limits.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include <stdbool.h>

// Log defines and default levels
//
// static const char * tag = "tag";
// #define TAG_LOGGING_DEFAULT_LEVEL ESP_WARN
//
// Remember to add to the setup of the log in main.c or in the relevant file
// before you use it!

static const char * LOG_MISC = "MISC";
static const char * LOG_LED = "LED";


#endif