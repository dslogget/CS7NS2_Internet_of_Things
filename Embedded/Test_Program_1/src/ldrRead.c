#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

const char * JSONmV = JSON_FORMAT_BUILDER( 1, "%dmV" );

#define NUMSAMPLES 35

static const char * LOG_LDR = "LDR";

void ldrRead( void * params ) {
    uint32_t adc_reading;
    char buf[ 128 ] =  { 0 };

    while( 1 ) {
        // Average of 5 samples reading
        adc_reading = 0;
        for (int i = 0; i < NUMSAMPLES; i++) {
                adc_reading += adc1_get_raw( CHANNEL_LDR );
        }
        adc_reading /= NUMSAMPLES;
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc1_chars);
        ESP_LOGI( LOG_LDR, "Raw: %d\tVoltage: %dmV\n", adc_reading, voltage );
        JSON_TO_BUF( JSONmV, 128, buf, "LDR1", voltage );
        ESP_LOGI( LOG_LDR, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 30 * 1000 / portTICK_PERIOD_MS );
    }
}