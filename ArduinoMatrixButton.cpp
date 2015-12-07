/*! \file */

#include "ArduinoMatrixButton.h"

/*!
 * \brief Creates a new button in a matrix configuration.
 * \param id ID of the button
 * \param colPin Pin connected to the matrix column of the button
 * \param rowPin PIn connected to the matrix row of the button
 */
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

/*!
 * \copydoc IButton::getPhysicalState
 */
uint8_t ArduinoMatrixButton::getPhysicalState()
{
  digitalWrite(m_colPin, LOW);
  uint8_t state = !digitalRead(m_rowPin);
  digitalWrite(m_colPin, HIGH);
  return state;
}
