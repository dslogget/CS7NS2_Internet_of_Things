#include "common.h"
#include "pinDefs.h"
#define HANDLES_IMPL
#include "globalHandles.h"
#include "tasksInclude.h"

static void initialiseLogs( void ) {
    esp_log_level_set( "*", ESP_LOG_WARN );
    esp_log_level_set( LOG_MISC, ESP_LOG_INFO );
    esp_log_level_set( LOG_LED, ESP_LOG_INFO );
}

static void startTasks( void ) {
    xTaskCreatePinnedToCore( &ledState, "ledState", 2048, NULL, 1, &ledStateTaskHandle, 1 );
    xTaskCreatePinnedToCore( &blinkLED, "blinkLED", 2048, NULL, 1, NULL, 1 );
}

static void initialisePins( void ) {
    gpio_config_t config = { GPIO_SEL_4,
                             GPIO_MODE_OUTPUT,
                             GPIO_PULLUP_DISABLE,
                             GPIO_PULLDOWN_DISABLE,
                             GPIO_INTR_DISABLE };

    ESP_ERROR_CHECK( gpio_config( &config ) );
}

static void setupQueues( void ) { 
    
}

void app_main() {
    initialiseLogs();

    ESP_LOGI( LOG_MISC, "Hello World!\n" );

    setupQueues();

    initialisePins();
    
    startTasks();

    fflush( stdout );
    vTaskDelete( NULL );
}