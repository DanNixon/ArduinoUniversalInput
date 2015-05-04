#ifndef ARDUINO_UNIVERSAL_INPUT_H
#define ARDUINO_UNIVERSAL_INPUT_H

#include <inttypes.h>


namespace UniversalInput
{
  typedef uint8_t pin_t;

  enum Result
  {
    RESULT_OK,
    RESULT_DEVICE_ALREADY_EXISTS,
    RESULT_NO_SUCH_DEVICE,
    RESULT_INVALID_PARAMETERS,
    RESULT_NO_CUSTOM_IO,
    RESULT_OUT_OF_RANGE,
    RESULT_IO_PIN_ALREADY_IN_USE
  };

  enum inputtype_t
  {
    UNIVERSAL_BUTTON,
    UNIVERSAL_JOYSTICK
  };

};

#endif