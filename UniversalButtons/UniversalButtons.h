#ifndef UNIVERSAL_BUTTONS_H
#define UNIVERSAL_BUTTONS_H

#include "UniversalInput.h"
#include <Arduino.h>
#include <inttypes.h>

#define DEFAULT_DEBOUNCE_DELAY 100

#define DEFAULT_PULLUP 1
#define DEFAULT_ACTIVE_LOW 1

using UniversalInput::pin_t;
typedef uint16_t buttonid_t;


/**
 * Represents types of buttons.
 */
enum ButtonType
{
  TYPE_GPIO_BASIC,
  TYPE_GPIO_MATRIX,
  TYPE_CUSTOM_BASIC,
  TYPE_CUSTOM_MATRIX
};


/**
 * Stores a button configuration in the linked list.
 */
struct Button
{
  buttonid_t id;
  ButtonType type;

  pin_t rowPin;
  pin_t columnPin;

  uint8_t activeLow;

  uint8_t (* pinRead) (pin_t pin);
  void (* pinWrite) (pin_t pin, uint8_t state);

  uint8_t lastState;
  uint32_t lastEdgeTime;

  Button *next;
};


/**
 * IO helper class for manaing button and switch input.
 */
class UniversalButtons
{
  public:
    UniversalButtons();
    ~UniversalButtons();

    void poll();

    void setStateChangeCallback(void (* callback)(buttonid_t bid, uint8_t state));
    void setStateCycleCallback(void (*callback)(buttonid_t bid, uint32_t timeHeld));

    uint16_t getDebounceDelay();
    void setDebounceDelay(uint16_t delay);

    void setCustomIO(uint8_t (* readPin) (pin_t pin), void (* writePin) (pin_t pin, uint8_t state));

    void setDefaultButtonConfig(uint8_t pullup, uint8_t activeLow);

    UniversalInput::Result addButton(pin_t pin);
    UniversalInput::Result addButton(buttonid_t bid, pin_t pin);
    UniversalInput::Result addButton(buttonid_t bid, pin_t pin, uint8_t pullup, uint8_t activeLow);
    UniversalInput::Result addButton(buttonid_t bid, pin_t rowPin, pin_t colPin);
    UniversalInput::Result addCustomButton(buttonid_t bid, pin_t pin);
    UniversalInput::Result addCustomButton(buttonid_t bid, pin_t pin, uint8_t pullup, uint8_t activeLow);
    UniversalInput::Result addCustomButton(buttonid_t bid, pin_t rowPin, pin_t colPin);

    UniversalInput::Result removeButton(buttonid_t bid);

    int8_t getButtonState(buttonid_t bid);
    uint32_t getTimeSinceLastChange(buttonid_t bid);

    uint16_t buttonCount();

  private:
    uint8_t readButtonState(Button *button);
    UniversalInput::Result buttonListAppend(Button *button);

    void (* m_stateChangeCallback)(buttonid_t bid, uint8_t state);
    void (* m_stateCycleCallback)(buttonid_t bid, uint32_t timeHeld);

    uint8_t (* m_readPinFunct)(pin_t pin);
    void (* m_writePinFunct)(pin_t pin, uint8_t state);

    uint8_t m_defaultActiveLow;
    uint8_t m_defaultPullup;

    uint16_t m_debounceDelay;

    uint16_t m_buttonCount;
    Button *m_buttonList;

};

#endif
