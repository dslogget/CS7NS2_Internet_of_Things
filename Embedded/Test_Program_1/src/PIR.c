#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

extern const char * JSON_1String;

static const char * LOG_MIC = "PIR";

static const char * const TOPIC = "homeAutomation/PIR1";

void PIRTask( void * params ) {
    uint32_t notification;
    ESP_LOGI( LOG_MIC, "PIR task started" );
    char buf[ 128 ];

    while ( 1 ) {
        JSON_TO_BUF( JSON_1String, 128, buf, "PIR" );
        xTaskNotifyWait( ULONG_MAX, ULONG_MAX, NULL, 0 );
        xTaskNotifyWait( ULONG_MAX,    /* Clear bits on entry. */
                         ULONG_MAX,        /* Clear all bits on exit. */
                         &notification, /* Stores the notified value. */
                         portMAX_DELAY );
        ESP_LOGI( LOG_MIC, "PIR triggered" );
        ESP_LOGI( LOG_MIC, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 10000 / portTICK_PERIOD_MS );
    }
}

void PIRISR( void * params ) { 
    xTaskNotifyFromISR( PIRTaskHandle, 1, eSetValueWithOverwrite, NULL );
}