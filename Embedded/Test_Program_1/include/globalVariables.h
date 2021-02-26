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
extern esp_adc_cal_characteristics_t * adc1_chars;
extern AWS_IoT_Client mqtt_client;
#else
// final example
// QueueHandle_t serialOutQueue = NULL;
TaskHandle_t ledStateTaskHandle = NULL;
esp_adc_cal_characteristics_t * adc1_chars = NULL;
AWS_IoT_Client mqtt_client;
#undef VARIABLES_IMPL
#endif

#endif