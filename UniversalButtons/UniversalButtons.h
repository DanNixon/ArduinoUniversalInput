/*
 * UniversalButtons button input library
 *
 * UniversalButtons
 * Dan Nixon, dan-nixon.com
 * 23/06/2014
 */

#ifndef UNIVERSAL_BUTTONS_H
#define UNIVERSAL_BUTTONS_H

#include <Arduino.h>
#include <inttypes.h>

#define DEFAULT_DEBOUCE_DELAY 250

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
  RESULT_INVALID_PARAMETERS
};

struct Button
{
  buttonid_t id;
  ButtonType type;
  
  uint8_t rowPin;
  uint8_t columnPin;
  
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
     * Sets the callback function used to handle event driven button input
     */
    void setCallback(void (* callback)(buttonid_t bid, uint8_t state));

    /*
     * Getter and setter for the debounce delay
     */
    uint16_t getDebounceDelay();
    void setDebounceDelay(uint16_t delay);

    /*
     * Adds a new basic pull high or pull low button using the board IO
     */
    Result addButton(buttonid_t bid, pin_t pin);

    /*
     * Adds a new matrix button using the board IO
     */
    Result addButton(buttonid_t bid, pin_t rowPin, pin_t colPin);

    /*
     * Adds a new basic button using a custom IO function
     */
    Result addButton(buttonid_t bid, pin_t pin,
        uint8_t (* pinRead) (pin_t pin));

    /*
     * Adds a new matrix button using a custom IO function
     */
    Result addButton(buttonid_t bid, pin_t rowPin, pin_t colPin,
        uint8_t (* pinRead) (pin_t pin), void (* pinSet) (pin_t pin, uint8_t state));

    /*
     * Removes a button
     */
    Result removeButton(buttonid_t bid);

    /*
     * Gets the last known state of a given button
     */
    int8_t getButtonState(buttonid_t bid);

    /*
     * Gets the number of buttons currently configured
     */
    uint16_t buttonCount();

  private:
    uint8_t readButtonState(Button *button);
    void buttonListAppend(Button *button);

    uint16_t _buttonCount;

    void (* _callback)(buttonid_t bid, uint8_t state);

    uint16_t _debounceDelay;

    Button *_buttonList;
};

#endif
