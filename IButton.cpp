/*! \file */

#include "IButton.h"

IButton::IButton(inputid_t id, inputtime_t debounceDelay)
    : IInputDevice(id)
    , m_active(false)
    , m_lastStateChange(0)
    , m_lastActiveDuration(0)
    , m_debounceDelay(debounceDelay)
{
}

IButton::~IButton()
{
}

bool IButton::setDebounceDelay(inputtime_t debounce)
{
  if (debounce <= 0)
    return false;

  m_debounceDelay = debounce;
  return true;
}

bool IButton::poll()
{
  if ((millis() - m_lastStateChange > m_debounceDelay) ||
      (m_lastStateChange == 0))
  {
    bool state = getPhysicalState();
    if (state != m_active)
    {
      if (!state)
        m_lastActiveDuration = millis() - m_lastStateChange;

      m_lastStateChange = millis();
      m_active = state;

      return true;
    }
  }

  return false;
}
