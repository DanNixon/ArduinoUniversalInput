#ifndef ARDUINO_UNIVERSAL_JOYSTICKS_H
#define ARDUINO_UNIVERSAL_JOYSTICKS_H

#include <Arduino.h>
#include <inttypes.h>
#include <UniversalInput.h>

#include "JoystickConfig.h"
#include "JoystickTypes.h"


using UniversalInput::pin_t;


/**
 * Holds data about a joystick in the linked list.
 */
struct joystick_t
{
  joystickid_t id;
  JoystickConfig *config;
  pin_t adcPin;
  joystickvalue_t (* adcRead) (pin_t pin);
  joystickvalue_t lastValue;
  joystick_t *next;
};


/**
 * IO helper class to manage joystick/potentiometer input.
 */
class UniversalJoysticks
{
  public:
    UniversalJoysticks();
    ~UniversalJoysticks();

    void poll();

    void setValueChangeCallback(void (* callback)(joystickid_t jid, joystickvalue_t value, joystickvalue_t delta));

    JoystickConfig *getDefaultConfig();
    void setDefaultConfig(JoystickConfig *config);

    JoystickConfig *getConfig(joystickid_t jid);

    void setCustomIO(joystickraw_t (* readADC)(pin_t pin));

    UniversalInput::result_t addJoystick(pin_t pin, JoystickConfig *config = NULL);
    UniversalInput::result_t addJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config = NULL);

    UniversalInput::result_t addCustomJoystick(pin_t pin, JoystickConfig *config = NULL);
    UniversalInput::result_t addCustomJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config = NULL);

    UniversalInput::result_t removeJoystick(joystickid_t jid);

    joystickvalue_t getJoystickValue(joystickid_t jid);

    uint16_t joystickCount();

  private:
    UniversalInput::result_t joystickListAppend(joystick_t *joystick);

    JoystickConfig *m_defaultConfig;

    joystickraw_t (* m_readADC)(pin_t pin);
    void (* m_valueChangeCallback)(joystickid_t jid, joystickvalue_t value, joystickvalue_t delta);

    uint16_t m_joystickCount;
    joystick_t *m_joystickList;

};

#endif
