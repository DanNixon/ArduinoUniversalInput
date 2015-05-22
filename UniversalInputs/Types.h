#ifndef _ARDUINOUNIVERSALINPUTS_TYPES_H
#define _ARDUINOUNIVERSALINPUTS_TYPES_H

#include <inttypes.h>

#define NULL 0
typedef uint16_t size_t;

typedef uint16_t inputid_t;
typedef uint8_t inputpin_t;
typedef uint32_t inputtime_t;

enum UniversalInputType
{
  UIT_BUTTON,
  UIT_JOYSTICK
};

#endif
