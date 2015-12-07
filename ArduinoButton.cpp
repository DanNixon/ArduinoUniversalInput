/*! \file */

#include "ArduinoButton.h"

/*!
 * \brief Creates a new button on an Arduino pin.
 * \param id ID of the button
 * \param pin Pin the button is attached to
 * \param activeLow If the button logic is active low
 * \param pullUp If the pin should be pulled high
 */
ArduinoButton::ArduinoButton(inputid_t id, inputpin_t pin, bool activeLow,
                             bool pullUp)
    : IButton(id)
    , m_pin(pin)
    , m_activeLow(activeLow)
    , m_pullUp(pullUp)
{
  if (pullUp)
    pinMode(pin, INPUT_PULLUP);
  else
    pinMode(pin, INPUT);
}

/*!
 * \copydoc IButton::getPhysicalState
 */
uint8_t ArduinoButton::getPhysicalState()
{
  if (m_activeLow)
    return !digitalRead(m_pin);
  else
    return digitalRead(m_pin);
}
