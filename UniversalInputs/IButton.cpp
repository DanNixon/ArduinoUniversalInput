#include "IButton.h"


IButton::IButton(inputid_t id, inputtime_t debounceDelay) :
  IInputDevice(id),
  m_active(false),
  m_lastStateChange(0),
  m_lastActiveDuration(0),
  m_debounceDelay(debounceDelay)
{
}


bool IButton::poll()
{
  if(millis() - m_lastStateChange > m_debounceDelay)
  {
    bool state = getPhysicalState();
    if(state != m_active)
    {
      if(!state)
        m_lastActiveDuration = millis() - m_lastStateChange;

      m_lastStateChange = millis();
      m_active = state;

      return true;
    }
  }

  return false;
}
