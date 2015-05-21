#include "ArduinoButton.h"

#include <Arduino.h>


ArduinoButton::ArduinoButton(inputid_t id, inputpin_t pin, bool activeLow, bool pullUp)
  : IButton(id), m_pin(pin), m_activeLow(activeLow), m_pullUp(pullUp)
{
  if(pullUp)
    pinMode(pin, INPUT_PULLUP);
  else
    pinMode(pin, INPUT);

  //TODO
}


bool ArduinoButton::poll()
{
  //TODO
  return false;
}

