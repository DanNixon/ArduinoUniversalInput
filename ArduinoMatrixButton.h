/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_ARDUINOMATRIXBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_ARDUINOMATRIXBUTTON_H

#include "IButton.h"

/*!
 * \class ArduinoMatrixButton
 * \brief Represents a single button in a matrix configuration.
 */
class ArduinoMatrixButton : public IButton
{
public:
  ArduinoMatrixButton(inputid_t id, inputpin_t colPin, inputpin_t rowPin);

  /*!
   * \brief Gets the pin attached to the matrix column for this button.
   * \rueturn Pin number
   */
  inputpin_t getColPin() { return m_colPin; }

  /*!
   * \brief Gets the pin attached to the matrix row for this button.
   * \rueturn Pin number
   */
  inputpin_t getRowPin() { return m_rowPin; }

protected:
  uint8_t getPhysicalState();

private:
  inputpin_t m_colPin; //!< Pin connected to button matrix column
  inputpin_t m_rowPin; //!< Pin connected to button matrix row
};

#endif
