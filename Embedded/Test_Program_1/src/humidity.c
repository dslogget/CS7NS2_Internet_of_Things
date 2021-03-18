#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

const char * JSON_1String = JSON_FORMAT_BUILDER( 1, "Triggered" );

static const char * LOG_HUMIDITY = "HUMIDITY";

static const char * const TOPIC = "homeAutomation/HUMIDITY0";

void humidityTask( void * params ) {
    uint32_t notification;
    ESP_LOGI( LOG_HUMIDITY, "Humidity task started" );
    char buf[ 128 ];

    while ( 1 ) {
        JSON_TO_BUF( JSON_1String, 128, buf, "Humidity" );
        xTaskNotifyWait( ULONG_MAX, ULONG_MAX, NULL, 0 );
        xTaskNotifyWait( ULONG_MAX,    /* Clear bits on entry. */
                         ULONG_MAX,        /* Clear all bits on exit. */
                         &notification, /* Stores the notified value. */
                         portMAX_DELAY );
        ESP_LOGI( LOG_HUMIDITY, "Humidity triggered" );
        ESP_LOGI( LOG_HUMIDITY, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 10000 / portTICK_PERIOD_MS );
    }
}

void humidityISR( void * params ) { 
    xTaskNotifyFromISR( humidityTaskHandle, 1, eSetValueWithOverwrite, NULL );
}