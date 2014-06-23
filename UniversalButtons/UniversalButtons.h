/*
 * UniversalButtons button input library
 *
 * ArduinoUniversalButtons
 * Dan Nixon, dan-nixon.com
 * 23/06/2014
 */

#ifndef UNIVERSAL_BUTTONS_H
#define UNIVERSAL_BUTTONS_H

#include <Arduino.h>
#include <inttypes.h>

#define DEFAULT_DEBOUCE_DELAY 100

#define DEFAULT_PULLUP 1
#define DEFAULT_ACTIVE_LOW 1

typedef uint16_t buttonid_t;
typedef uint8_t pin_t;

enum ButtonType
{
  TYPE_GPIO_BASIC,
  TYPE_GPIO_MATRIX,
  TYPE_CUSTOM_BASIC,
  TYPE_CUSTOM_MATRIX
};

enum Result
{
  RESULT_OK,
  RESULT_BUTTON_ALREADY_EXISTS,
  RESULT_NO_SUCH_BUTTON,
  RESULT_INVALID_PARAMETERS,
  RESULT_NO_CUSTOM_IO
};

struct Button
{
  buttonid_t id;
  ButtonType type;
  
  uint8_t rowPin;
  uint8_t columnPin;
  
  uint8_t activeLow;

  uint8_t (* pinRead) (pin_t pin);
  void (* pinWrite) (pin_t pin, uint8_t state);

  uint8_t lastState;
  uint32_t lastEdgeTime;

  Button *next;
};

class UniversalButtons
{
  public:
    UniversalButtons();
    ~UniversalButtons();

    /*
     * Updates the states of the buttons and calls callback function when needed
     */
    void poll();

    /*
     * Sets the callback function used to handle the state of a button changing
     * i.e. either a push or release of a button
     * Callback function takes button ID and new state of button
     */
    void setStateChangeCallback(
        void (* callback)(buttonid_t bid, uint8_t state));

    /*
     * Sets the callback function used to handle a button being pushed and
     * released
     * Callback function takes button ID and length of tiem the button was held
     * (in milliseconds)
     */
    void setStateCycleCallback(void (*callback)(buttonid_t bid,
          uint32_t timeHeld));

    /*
     * Getter and setter for the debounce delay
     */
    uint16_t getDebounceDelay();
    void setDebounceDelay(uint16_t delay);

    /*
     * Setter for custom IO logic functions
     * Only effects calls makde to addCustomButton() after it is called
     */
    void setCustomIO(uint8_t (* readPin) (pin_t pin),
        void (* writePin) (pin_t pin, uint8_t state));

    /*
     * Sets the default logic configuration for simple buttons
     */
    void setDefaultButtonConfig(uint8_t pullup, uint8_t activeLow);

    /*
     * Adds a new basic pull high or pull low button using the board IO
     */
    Result addButton(buttonid_t bid, pin_t pin);
    Result addButton(buttonid_t bid, pin_t pin,
        uint8_t pullup, uint8_t activeLow);

    /*
     * Adds a new matrix button using the board IO
     */
    Result addButton(buttonid_t bid, pin_t rowPin, pin_t colPin);

    /*
     * Adds a new basic button using a custom IO function defined with
     * setCustomIO()
     */
    Result addCustomButton(buttonid_t bid, pin_t pin);
    Result addCustomButton(buttonid_t bid, pin_t pin,
        uint8_t pullup, uint8_t activeLow);

    /*
     * Adds a new matrix button using a custom IO function defined with
     * setCustomIO()
     */
    Result addCustomButton(buttonid_t bid, pin_t rowPin, pin_t colPin);

    /*
     * Removes a button
     */
    Result removeButton(buttonid_t bid);

    /*
     * Gets the last known state of a given button
     */
    int8_t getButtonState(buttonid_t bid);

    /*
     * Gets the amount of time (in milliseconds) the button has been in it's
     * current state
     */
    uint32_t getTimeSinceLastChange(buttonid_t bid);

    /*
     * Gets the number of buttons currently configured
     */
    uint16_t buttonCount();

  private:
    uint8_t readButtonState(Button *button);
    void buttonListAppend(Button *button);

    uint16_t _buttonCount;

    void (* _stateChangeCallback)(buttonid_t bid, uint8_t state);
    void (* _stateCycleCallback)(buttonid_t bid, uint32_t timeHeld);

    uint8_t (* _readPinFunct)(pin_t pin);
    void (* _writePinFunct)(pin_t pin, uint8_t state);

    uint8_t _defaultActiveLow;
    uint8_t _defaultPullup;

    uint16_t _debounceDelay;

    Button *_buttonList;
};

#endif
