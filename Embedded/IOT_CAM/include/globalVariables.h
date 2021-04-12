#ifndef GLOBAL_VARIABLES_H_GUARD
#define GLOBAL_VARIABLES_H_GUARD
#include <stdio.h>


// example for a queue of queueName
// #define QUEUE_NAME_MESSAGE_LENGTH 512
// #define QUEUE_NAME_MESSAGE_SIZE QUEUE_NAME_MESSAGE_LENGTH * sizeof( char )

#ifndef VARIABLES_IMPL
// example continued
// extern QueueHandle_t queueName;
extern uint8_t MAC_ADDRESS[ 6 ];
#else
uint8_t MAC_ADDRESS[ 6 ] = { 0 };
#endif

#endif