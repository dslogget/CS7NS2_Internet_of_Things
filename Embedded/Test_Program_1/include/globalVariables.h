#ifndef GLOBAL_VARIABLES_H_GUARD
#define GLOBAL_VARIABLES_H_GUARD
#include "common.h"


// example for a queue of queueName
// #define QUEUE_NAME_MESSAGE_LENGTH 512
// #define QUEUE_NAME_MESSAGE_SIZE QUEUE_NAME_MESSAGE_LENGTH * sizeof( char )

#ifndef VARIABLES_IMPL
// example continued
// extern QueueHandle_t queueName;
extern TaskHandle_t ledStateTaskHandle;
extern TaskHandle_t microphoneTaskHandle;
extern esp_adc_cal_characteristics_t * adc1_chars;
extern esp_mqtt_client_handle_t mqttClient;
extern uint8_t MAC_ADDRESS[ 6 ];
#else
// final example
// QueueHandle_t serialOutQueue = NULL;
TaskHandle_t ledStateTaskHandle = NULL;
TaskHandle_t microphoneTaskHandle = NULL;
esp_adc_cal_characteristics_t * adc1_chars = NULL;
esp_mqtt_client_handle_t mqttClient = NULL;
uint8_t MAC_ADDRESS[ 6 ] = { 0 };
#undef VARIABLES_IMPL
#endif

#endif