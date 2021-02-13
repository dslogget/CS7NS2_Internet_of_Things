#include "common.h"
#include "pinDefs.h"
#include "globalHandles.h"

void blinkLED( void * params ) {
    ESP_LOGI( LOG_MISC, "blinkLED Started!" );
    while( 1 ) {
        ESP_LOGI( LOG_LED, "Notifying set high" );
        xTaskNotify( ledStateTaskHandle, 1, eSetValueWithOverwrite );
        ESP_LOGI( LOG_LED, "Notified set high" );
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        ESP_LOGI( LOG_LED, "Notifying set low" );
        xTaskNotify( ledStateTaskHandle, 0, eSetValueWithOverwrite );
        ESP_LOGI( LOG_LED, "Notified set low" );
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}