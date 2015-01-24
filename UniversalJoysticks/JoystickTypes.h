#ifndef ARDUINO_UNIVERSAL_JOYSTICKS_TYPES_H
#define ARDUINO_UNIVERSAL_JOYSTICKS_TYPES_H

#include <inttypes.h>


// Represents the ID of a joystick
typedef uint16_t joystickid_t;

// Represents the mapped joystick values
typedef int32_t joystickvalue_t;

// Represents a raw value read from the ADC
typedef int32_t joystickraw_t;


#define INT32_MAX 0x7fffffffL
#define INT32_MIN (-INT32_MAX - 1L)

#endif
