/*! \file */

#include "MCP23017Button.h"

/*!
 * \brief Creates a new button on an MCP23017 GPIO pin.
 * \param io Pointer to the MCP23017 driver
 * \param id ID of the button
 * \param pin Pin the button is attached to
 * \param activeLow If the button logic is active low
 * \param pullUp If the pin should be pulled high
 */
MCP23017Button::MCP23017Button(Adafruit_MCP23017 *io, inputid_t id,
                               inputpin_t pin, bool activeLow, bool pullUp)
    : IButton(id)
    , m_io(io)
    , m_pin(pin)
    , m_activeLow(activeLow)
    , m_pullUp(pullUp)
{
  m_io->pinMode(m_pin, INPUT);

  if (pullUp)
    m_io->pullUp(m_pin, HIGH);

  m_io->setupInterruptPin(m_pin, CHANGE);
}

/*!
 * \copydoc IButton::getPhysicalState
 */
uint8_t MCP23017Button::getPhysicalState() const
{
  if (m_activeLow)
    return !m_io->digitalRead(m_pin);
  else
    return m_io->digitalRead(m_pin);
}
