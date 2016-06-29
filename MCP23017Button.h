/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_MCP23017BUTTON_H
#define _ARDUINOUNIVERSALINPUTS_MCP23017BUTTON_H

#include "IButton.h"

#include <Adafruit_MCP23017.h>

/*!
 * \class MCP23017Button
 * \brief Represents a button on an MCP23017 GPIO pin.
 */
class MCP23017Button : public IButton
{
public:
  MCP23017Button(Adafruit_MCP23017 *io, inputid_t id, inputpin_t pin,
                 bool activeLow = true, bool pullUp = true);

  virtual ~MCP23017Button()
  {
  }

  /*!
   * \brief Gets the pin the button is attached to.
   * \return Pin number
   */
  inputpin_t getPin() const
  {
    return m_pin;
  }

  /*!
   * \brief Determines if the pin logic is active low.
   * \return True if active low
   */
  bool isActiveLow() const
  {
    return m_activeLow;
  }

  /*!
   * \brief Determines if the pin is pulled high.
   * \return True if pull up active
   */
  bool isPullUp() const
  {
    return m_pullUp;
  }

protected:
  uint8_t getPhysicalState() const;

private:
  Adafruit_MCP23017 *m_io; //!< Pointer to IO driver
  inputpin_t m_pin;        //!< Pin button is attached to
  bool m_activeLow;        //!< If the button logic is active low
  bool m_pullUp;           //!< If the button pin is pulled up
};

#endif
