#ifndef _ARDUINOUNIVERSALINPUTS_TYPES_H
#define _ARDUINOUNIVERSALINPUTS_TYPES_H

#include <Arduino.h>
#include <inttypes.h>

#define NULL 0

typedef uint16_t inputid_t;
typedef uint8_t inputpin_t;
typedef uint32_t inputtime_t;
typedef int32_t inputanalog_t;

enum inputtype_t
{
  UIT_BUTTON,
  UIT_JOYSTICK
};

#endif
