
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_4

void blinkLED( void * params ) {
    while( 1 ) {
        ESP_ERROR_CHECK( gpio_set_level( LED_PIN, 1 ) );
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        ESP_ERROR_CHECK( gpio_set_level( LED_PIN, 0 ) );
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}


void app_main() {
    printf( "Hello world!" );

    gpio_config_t config = { GPIO_SEL_4,
                             GPIO_MODE_OUTPUT,
                             GPIO_PULLUP_DISABLE,
                             GPIO_PULLDOWN_DISABLE,
                             GPIO_INTR_DISABLE };

    ESP_ERROR_CHECK( gpio_config( &config ) );
    
    xTaskCreate( &blinkLED, "blinkLED", 1000, NULL, 1, NULL );
    fflush( stdout );
    vTaskDelete( NULL );
}