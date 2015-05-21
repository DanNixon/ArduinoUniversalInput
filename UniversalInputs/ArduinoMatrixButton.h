#ifndef _ARDUINOUNIVERSALINPUTS_ARDUINOMATRIXBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_ARDUINOMATRIXBUTTON_H

#include "IButton.h"


class ArduinoMatrixButton : public IButton
{
  public:
    ArduinoMatrixButton(inputid_t id, inputpin_t colPin, inputpin_t rowPin);

    inputpin_t getColPin() { return m_colPin; }
    inputpin_t getRowPin() { return m_rowPin; }

  protected:
    uint8_t getPhysicalState();

  private:
    inputpin_t m_colPin;
    inputpin_t m_rowPin;

};

#endif
