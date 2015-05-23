#include "ArduinoButton.h"


ArduinoButton::ArduinoButton(inputid_t id, inputpin_t pin, bool activeLow, bool pullUp) :
  IButton(id),
  m_pin(pin),
  m_activeLow(activeLow),
  m_pullUp(pullUp)
{
  if(pullUp)
    pinMode(pin, INPUT_PULLUP);
  else
    pinMode(pin, INPUT);
}


uint8_t ArduinoButton::getPhysicalState()
{
  if(m_activeLow)
    return !digitalRead(m_pin);
  else
    return digitalRead(m_pin);
}

