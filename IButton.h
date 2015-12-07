/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_IBUTTON_H

#include "IInputDevice.h"

#include "Arduino.h"

/*!
 * \class IButton
 * \brief Represents a two state button.
 */
class IButton : public IInputDevice
{
public:
  IButton(inputid_t id, inputtime_t debounceDelay = 50);
  virtual ~IButton();

  /*!
   * \copydoc IInputDevice::type
   */
  inputtype_t type() { return UIT_BUTTON; }

  bool setDebounceDelay(inputtime_t debounce);

  /*!
   * \brief Gets the current debounce delay time.
   * \return Debounce delay in ms
   */
  inputtime_t getDebounceDelay() { return m_debounceDelay; }

  bool poll();

  /*!
   * \brief Determines if the button is currently active.
   * \return True of button is active
   */
  bool isActive() { return m_active; }

  /*!
   * \brief Returns the time of the last state change.
   * \return Time in ms
   */
  inputtime_t lastStateChange() { return m_lastStateChange; }

  /*!
   * \brief Returns the duration for which the button was last active.
   * \return Duration in ms
   */
  inputtime_t lastActiveDuration() { return m_lastActiveDuration; }

protected:
  /*!
   * \brief Gets the current physical state of the button.
   * \return True if button state is high
   */
  virtual uint8_t getPhysicalState() = 0;

private:
  bool m_active; //!< Current active state of the button

  inputtime_t m_lastStateChange; //!< Time of last state change
  inputtime_t m_lastActiveDuration; //!< Duration of last active state

  inputtime_t m_debounceDelay; //!< Debounce delay time
};

#endif
