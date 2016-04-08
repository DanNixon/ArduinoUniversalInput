/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_ARDUINOBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_ARDUINOBUTTON_H

#include "IButton.h"

/*!
 * \class ArduinoButton
 * \brief Represents a button on an Arduino pin.
 */
class ArduinoButton : public IButton
{
public:
  ArduinoButton(inputid_t id, inputpin_t pin, bool activeLow = true,
                bool pullUp = true);

  virtual ~ArduinoButton() {}

  /*!
   * \brief Gets the pin the button is attached to.
   * \return Pin number
   */
  inputpin_t getPin() const { return m_pin; }

  /*!
   * \brief Determines if the pin logic is active low.
   * \return True if active low
   */
  bool isActiveLow() const { return m_activeLow; }

  /*!
   * \brief Determines if the pin is pulled high.
   * \return True if pull up active
   */
  bool isPullUp() const { return m_pullUp; }

protected:
  uint8_t getPhysicalState() const;

private:
  inputpin_t m_pin; //!< Pin button is attached to
  bool m_activeLow; //!< If the button logic is active low
  bool m_pullUp;    //!< If the button pin is pulled up
};

#endif
