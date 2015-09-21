#ifndef _ARDUINOUNIVERSALINPUTS_ARDUINOJOYSTICK_H
#define _ARDUINOUNIVERSALINPUTS_ARDUINOJOYSTICK_H

#include "IJoystick.h"

class ArduinoJoystick : public IJoystick
{
public:
  ArduinoJoystick(inputid_t id, inputpin_t adc);

protected:
  inputanalog_t getPhysicalValue();

private:
  inputpin_t m_adcPin;
};

#endif
