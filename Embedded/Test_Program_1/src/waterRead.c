#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"
#include "jsonGen.h"

extern const char * JSONmV;

#define NUMSAMPLES 35

static const char * LOG_WATER = "WATER";

static const char * const TOPIC = "homeAutomation/WATER1";

void waterRead( void * params ) {
    uint32_t adc_reading;
    char buf[ 128 ] =  { 0 };

    while( 1 ) {
        // Average of 5 samples reading
        adc_reading = 0;
        for (int i = 0; i < NUMSAMPLES; i++) {
                adc_reading += adc1_get_raw( CHANNEL_WATER );
        }
        adc_reading /= NUMSAMPLES;
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc1_chars);
        ESP_LOGI( LOG_WATER, "Raw: %d\tVoltage: %dmV\n", adc_reading, voltage );
        JSON_TO_BUF( JSONmV, 128, buf, "Voltage", voltage );
        ESP_LOGI( LOG_WATER, "JSON: %s", buf );
        esp_mqtt_client_publish( mqttClient, TOPIC, buf, 0, 1, 0 );
        vTaskDelay( 30 * 1000 / portTICK_PERIOD_MS );
    }
}
