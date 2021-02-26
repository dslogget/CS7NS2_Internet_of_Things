#include "common.h"
#include "pinDefs.h"
#include "globalVariables.h"


#define NUMSAMPLES 35

static const char * LOG_LDR = "LDR";

static const char * const TOPIC = "homeAutomation/LDR1";


void ldrRead( void * params ) {
    const int TOPIC_LEN = strlen( TOPIC );
    uint32_t adc_reading;
    char buff[ 50 ] = { 0 };
    IoT_Publish_Message_Params toPublish;
    toPublish.qos = QOS0;
    toPublish.isRetained = 0;
    toPublish.payload = buff;

    while( 1 ) {
        // Average of 5 samples reading
        adc_reading = 0;
        for (int i = 0; i < NUMSAMPLES; i++) {
                adc_reading += adc1_get_raw( CHANNEL_LDR );
        }
        adc_reading /= NUMSAMPLES;
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc1_chars);
        ESP_LOGI( LOG_LDR, "Raw: %d\tVoltage: %dmV\n", adc_reading, voltage );
        sprintf( buff, "%dmV", voltage );

        toPublish.payloadLen = strlen( buff );
        aws_iot_mqtt_publish(&mqtt_client, "homeAutomation/LDR1", TOPIC_LEN, &toPublish);
        vTaskDelay( 30 * 1000 / portTICK_PERIOD_MS );
    }
}