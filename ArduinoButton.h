/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_ARDUINOBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_ARDUINOBUTTON_H

#include "IButton.h"

class ArduinoButton : public IButton
{
public:
  ArduinoButton(inputid_t id, inputpin_t pin, bool activeLow = true,
                bool pullUp = true);

  inputpin_t getPin() { return m_pin; }
  bool isActiveLow() { return m_activeLow; }
  bool isPullUp() { return m_pullUp; }

protected:
  uint8_t getPhysicalState();

private:
  inputpin_t m_pin;
  bool m_activeLow;
  bool m_pullUp;
};

#endif
