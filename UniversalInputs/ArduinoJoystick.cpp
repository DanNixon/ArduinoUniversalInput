#include "ArduinoJoystick.h"

#include "Arduino.h"


ArduinoJoystick::ArduinoJoystick(inputid_t id, inputpin_t adc) :
  IJoystick(id),
  m_adcPin(adc)
{
  setPoints(0, 512, 1024);
}


inputanalog_t ArduinoJoystick::getPhysicalValue()
{
  return analogRead(m_adcPin);
}
