#include "ArduinoMatrixButton.h"


ArduinoMatrixButton::ArduinoMatrixButton(inputid_t id, inputpin_t colPin, inputpin_t rowPin) :
  IButton(id),
  m_colPin(colPin),
  m_rowPin(rowPin)
{
  pinMode(colPin, OUTPUT);
  digitalWrite(colPin, LOW);

  pinMode(rowPin, INPUT);
}


uint8_t ArduinoMatrixButton::getPhysicalState()
{
  digitalWrite(m_colPin, HIGH);
  uint8_t state = digitalRead(m_rowPin);
  digitalWrite(m_colPin, LOW);
  return state;
}

