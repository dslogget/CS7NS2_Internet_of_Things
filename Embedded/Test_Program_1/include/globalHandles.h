#ifndef GLOBAL_HANDLES_H_GUARD
#define GLOBAL_HANDLES_H_GUARD
#include "freertos/queue.h"

// example for a queue of queueName
// #define QUEUE_NAME_MESSAGE_LENGTH 512
// #define QUEUE_NAME_MESSAGE_SIZE QUEUE_NAME_MESSAGE_LENGTH * sizeof( char )

#ifndef HANDLES_IMPL
// example continued
// extern QueueHandle_t queueName;
extern TaskHandle_t ledStateTaskHandle;

#else
// final example
// QueueHandle_t serialOutQueue = NULL;
TaskHandle_t ledStateTaskHandle = NULL;
#undef HANDLES_IMPL
#endif

#endif