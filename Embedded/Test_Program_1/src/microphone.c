#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

const char * JSON_1String = JSON_FORMAT_BUILDER( 1, "Triggered" );

static const char * LOG_MIC = "MIC";

static const char * const TOPIC = "homeAutomation/MICROPHONE1";

void microphoneTask( void * params ) {
    uint32_t notification;
    ESP_LOGI( LOG_MIC, "Microphone task started" );
    char buf[ 128 ];

    while ( 1 ) {
        JSON_TO_BUF( JSON_1String, 128, buf, "Microphone" );
        xTaskNotifyWait( ULONG_MAX, ULONG_MAX, NULL, 0 );
        xTaskNotifyWait( ULONG_MAX,    /* Clear bits on entry. */
                         ULONG_MAX,        /* Clear all bits on exit. */
                         &notification, /* Stores the notified value. */
                         portMAX_DELAY );
        ESP_LOGI( LOG_MIC, "Microphone triggered" );
        ESP_LOGI( LOG_MIC, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 10000 / portTICK_PERIOD_MS );
    }
}

void microphoneISR( void * params ) { 
    xTaskNotifyFromISR( microphoneTaskHandle, 1, eSetValueWithOverwrite, NULL );
}