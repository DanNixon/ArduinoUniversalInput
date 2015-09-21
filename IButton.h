#ifndef _ARDUINOUNIVERSALINPUTS_IBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_IBUTTON_H

#include "IInputDevice.h"

#include "Arduino.h"

class IButton : public IInputDevice
{
public:
  IButton(inputid_t id, inputtime_t debounceDelay = 50);

  inputtype_t type() { return UIT_BUTTON; }

  bool setDebounceDelay(inputtime_t debounce);
  inputtime_t getDebounceDelay() { return m_debounceDelay; }

  bool poll();

  bool isActive() { return m_active; }
  inputtime_t lastStateChange() { return m_lastStateChange; }
  inputtime_t lastActiveDuration() { return m_lastActiveDuration; }

protected:
  virtual uint8_t getPhysicalState() = 0;

private:
  bool m_active;

  inputtime_t m_lastStateChange;
  inputtime_t m_lastActiveDuration;

  inputtime_t m_debounceDelay;
};

#endif
