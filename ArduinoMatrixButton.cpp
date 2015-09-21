#include "ArduinoMatrixButton.h"

ArduinoMatrixButton::ArduinoMatrixButton(inputid_t id, inputpin_t colPin,
                                         inputpin_t rowPin)
    : IButton(id)
    , m_colPin(colPin)
    , m_rowPin(rowPin)
{
  pinMode(colPin, OUTPUT);
  digitalWrite(colPin, HIGH);

  pinMode(rowPin, INPUT_PULLUP);
}

uint8_t ArduinoMatrixButton::getPhysicalState()
{
  digitalWrite(m_colPin, LOW);
  uint8_t state = !digitalRead(m_rowPin);
  digitalWrite(m_colPin, HIGH);
  return state;
}
