#ifndef TASKS_INCLUDE_H_GUARD
#define TASKS_INCLUDE_H_GUARD

void blinkLED( void * params );
void ledState( void * params );
void ldrRead( void * params );
void waterRead( void * params );
void microphoneTask( void * params );
void PIRTask( void * params );
void ultrasonicTask( void * params );

#endif
