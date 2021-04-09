#ifndef GENERAL_HELPERS_H_GUARD
#define GENERAL_HELPERS_H_GUARD
#include "common.h"

uint32_t servoDegreesToPulseLength( uint32_t degrees );

void servoInit( void );

void servoSetAngle( uint32_t degrees );

#endif