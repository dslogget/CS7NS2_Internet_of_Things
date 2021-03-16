#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

const char * JSON_1String = JSON_FORMAT_BUILDER( 1, "Triggered" );

static const char * LOG_WATER = "WATER";

static const char * const TOPIC = "homeAutomation/WATER0";

void waterTask( void * params ) {
    uint32_t notification;
    ESP_LOGI( LOG_WATER, "Water task started" );
    char buf[ 128 ];

    while ( 1 ) {
        JSON_TO_BUF( JSON_1String, 128, buf, "Water" );
        xTaskNotifyWait( ULONG_MAX, ULONG_MAX, NULL, 0 );
        xTaskNotifyWait( ULONG_MAX,    /* Clear bits on entry. */
                         ULONG_MAX,        /* Clear all bits on exit. */
                         &notification, /* Stores the notified value. */
                         portMAX_DELAY );
        ESP_LOGI( LOG_WATER, "Water triggered" );
        ESP_LOGI( LOG_WATER, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 10000 / portTICK_PERIOD_MS );
    }
}

void waterISR( void * params ) { 
    xTaskNotifyFromISR( waterTaskHandle, 1, eSetValueWithOverwrite, NULL );
}