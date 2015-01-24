#include <UniversalButtons.h>


using namespace UniversalInput;


UniversalButtons::UniversalButtons() :
  m_stateChangeCallback(NULL),
  m_stateCycleCallback(NULL),

  m_readPinFunct(NULL),
  m_writePinFunct(NULL),

  m_debounceDelay(DEFAULT_DEBOUNCE_DELAY),

  m_buttonCount(0),
  m_buttonList(NULL)
{
}


UniversalButtons::~UniversalButtons()
{
  delete m_buttonList;
}


/**
 * Reads the state of a button using the configuration provided.
 *
 * @param button Button configuration
 * @return STate of button
 */
uint8_t UniversalButtons::readButtonState(Button *button)
{
  uint8_t state;

  switch(button->type)
  {
    case TYPE_GPIO_BASIC:
    case TYPE_CUSTOM_BASIC:
      state = button->pinRead(button->rowPin);
      if(button->activeLow)
        state = !state;
      break;

    case TYPE_GPIO_MATRIX:
    case TYPE_CUSTOM_MATRIX:
      button->pinWrite(button->columnPin, LOW);
      state = !(button->pinRead(button->rowPin));
      button->pinWrite(button->columnPin, HIGH);
      break;
  }

  return state;
}


/**
 * Checks all buttons for state changes and calls callback functions.
 */
void UniversalButtons::poll()
{
  uint8_t buttonState;
  Button *button = m_buttonList;

  while(button)
  {
    if((millis() - button->lastEdgeTime) > m_debounceDelay)
    {
      buttonState = readButtonState(button);

      if(buttonState != button->lastState)
      {
        if(m_stateChangeCallback)
          m_stateChangeCallback(button->id, buttonState);

        if(!buttonState && m_stateCycleCallback)
        {
          uint32_t deltaT = millis() - button->lastEdgeTime;
          m_stateCycleCallback(button->id, deltaT);
        }

        button->lastEdgeTime = millis();
      }

      button->lastState = buttonState;
    }

    button = button->next;
  }
}


/**
 * Sets the callback for when a button state changes.
 *
 * @param callback Callback function
 */
void UniversalButtons::setStateChangeCallback(void (* callback)(buttonid_t bid, uint8_t state))
{
  m_stateChangeCallback = callback;
}


/**
 * Sets the callback for twhen s button state is toggled.
 *
 * @param callback Callback function
 */
void UniversalButtons::setStateCycleCallback(void (* callback)(buttonid_t bid, uint32_t timeHeld))
{
  m_stateCycleCallback = callback;
}


/**
 * Adds a button to the linked list.
 *
 * @param button Button to add
 * @return Result of addition
 */
Result UniversalButtons::buttonListAppend(Button *button)
{
  if(!m_buttonList)
  {
    m_buttonList = button;
    m_buttonCount++;
    return RESULT_OK;
  }
  else
  {
    Button *ptr = m_buttonList;

    while(ptr->next)
    {
      ptr = ptr->next;
    }

    ptr->next = button;
  }

  m_buttonCount++;
  return RESULT_OK;
}


/**
 * Adds a buton.
 *
 * @param bid ID of new button
 * @param pin IO pin
 * @param pullup If the button should be pulled up
 * @param activeLow If the button is active low
 * @return Result of addition
 */
Result UniversalButtons::addButton(buttonid_t bid, pin_t pin,
    uint8_t pullup, uint8_t activeLow)
{
  Button *newButton = new Button;
  newButton->type = TYPE_GPIO_BASIC;
  newButton->id = bid;
  newButton->rowPin = pin;
  newButton->columnPin = 0;
  newButton->pinRead = (uint8_t (*) (pin_t)) &digitalRead;
  newButton->pinWrite = NULL;
  newButton->activeLow = activeLow;
  newButton->next = NULL;

  pinMode(pin, INPUT);
  if(pullup)
  {
    digitalWrite(pin, HIGH);
  }

  return buttonListAppend(newButton);
}


/**
 * Adds a buton.
 *
 * @param bid ID of new button
 * @param pin IO pin
 * @param pullup If the button should be pulled up
 * @param activeLow If the button is active low
 * @return Result of addition
 */
Result UniversalButtons::addButton(buttonid_t bid, pin_t pin)
{
  return addButton(bid, pin, m_defaultPullup, m_defaultActiveLow);
}


/**
 * Adds a buttom using default configuration.
 *
 * @param bid ID of new button
 * @param pin IO pin
 * @return Result of addition
 */
Result UniversalButtons::addButton(pin_t pin)
{
  return addButton(pin, pin, m_defaultPullup, m_defaultActiveLow);
}


/**
 * Adds a matrix button.
 *
 * @param bid ID of new button
 * @param rowPin IO pin for row
 * @param colPin IO pin for column
 * @param pullup If the button should be pulled up
 * @param activeLow If the button is active low
 * @return Result of addition
 */
Result UniversalButtons::addButton(buttonid_t bid, pin_t rowPin, pin_t colPin)
{
  Button *newButton = new Button;
  newButton->type = TYPE_GPIO_MATRIX;
  newButton->id = bid;
  newButton->rowPin = rowPin;
  newButton->columnPin = colPin;
  newButton->pinRead = (uint8_t (*) (pin_t)) &digitalRead;
  newButton->pinWrite = (void (*) (pin_t, uint8_t)) &digitalWrite;
  newButton->activeLow = 0;
  newButton->next = NULL;

  pinMode(rowPin, INPUT);
  pinMode(colPin, OUTPUT);

  digitalWrite(rowPin, HIGH);
  digitalWrite(colPin, HIGH);

  return buttonListAppend(newButton);
}


/**
 * Adds a custom button.
 *
 * @param bid ID of new button
 * @param pin IO pin
 * @param pullup If the button should be pulled up
 * @param activeLow If the button is active low
 * @return Result of addition
 */
Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t pin,
    uint8_t pullup, uint8_t activeLow)
{
  if(!(m_readPinFunct && m_writePinFunct))
    return RESULT_NO_CUSTOM_IO;

  Button *newButton = new Button;
  newButton->type = TYPE_CUSTOM_BASIC;
  newButton->id = bid;
  newButton->rowPin = pin;
  newButton->columnPin = 0;
  newButton->pinRead = m_readPinFunct;
  newButton->pinWrite = m_writePinFunct;
  newButton->activeLow = activeLow;
  newButton->next = NULL;

  if(pullup)
  {
    m_writePinFunct(pin, 1);
  }

  return buttonListAppend(newButton);
}


/**
 * Adds a custom button using default configuration.
 *
 * @param bid ID of new button
 * @param pin IO pin
 * @return Result of addition
 */
Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t pin)
{
  return addCustomButton(bid, pin, m_defaultPullup, m_defaultActiveLow);
}


/**
 * Adds a custom matrix button.
 *
 * @param bid ID of new button
 * @param rowPin IO pin for row
 * @param colPin IO pin for column
 * @return Result of addition
 */
Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t rowPin, pin_t colPin)
{
  if(!( m_readPinFunct && m_writePinFunct))
    return RESULT_NO_CUSTOM_IO;

  Button *newButton = new Button;
  newButton->type = TYPE_CUSTOM_MATRIX;
  newButton->id = bid;
  newButton->rowPin = rowPin;
  newButton->columnPin = colPin;
  newButton->pinRead = m_readPinFunct;
  newButton->pinWrite = m_writePinFunct;
  newButton->activeLow = 0;
  newButton->next = NULL;

  return buttonListAppend(newButton);
}


/**
 * Removes a button from the linked list.
 *
 * @param bid Button ID
 */
Result UniversalButtons::removeButton(buttonid_t bid)
{
  if(m_buttonCount == 0)
  {
    return RESULT_NO_SUCH_DEVICE;
  }
  if(m_buttonCount == 1)
  {
    if(m_buttonList->id == bid)
    {
      delete m_buttonList;
      m_buttonCount--;

      return RESULT_OK;
    }
  }
  else
  {
    Button *prev = NULL;
    Button *current = m_buttonList;

    while(current)
    {

      if(current->id == bid)
      {
        if(current->next)
        {
          if(prev)
            prev->next = current->next;
          else
            m_buttonList = current->next;
        }

        delete current;

        return RESULT_OK;
      }

      prev = current;
      current = current->next;
    }
  }

  return RESULT_NO_SUCH_DEVICE;
}


/**
 * Gets the current debounce delay.
 *
 * @return Debounce delay in ms
 */
uint16_t UniversalButtons::getDebounceDelay()
{
  return m_debounceDelay;
}


/**
 * Sets the debounce delay in milliseconds.
 *
 * @param delay Delay in ms
 */
void UniversalButtons::setDebounceDelay(uint16_t delay)
{
  m_debounceDelay = delay;
}


/**
 * Gets the last recorded state of a given button by ID.
 *
 * @param bid Button ID
 * @return Last recorded state
 */
int8_t UniversalButtons::getButtonState(buttonid_t bid)
{
  Button *button = m_buttonList;

  while(button)
  {
    if(button->id == bid)
      return button->lastState;

    button = button->next;
  }

  return -1;
}


/**
 * Gets the amount of time (in milliseconds) the button has been in it's
 * current state
 *
 * @pram bid Button ID
 * @return TIme in milliseconds
 */
uint32_t UniversalButtons::getTimeSinceLastChange(buttonid_t bid)
{
  Button *button = m_buttonList;

  while(button)
  {
    if(button->id == bid)
      return (millis() - button->lastEdgeTime);

    button = button->next;
  }

  return 0;
}


/**
 * Gets the number of buttons currently configured.
 *
 * @return Number of buttons
 */
uint16_t UniversalButtons::buttonCount()
{
  return m_buttonCount;
}


/**
 * Sets the custom IO functions for further custom buttons added.
 *
 * @param readPin Pin read function
 * @param writePin Pin write function
 */
void UniversalButtons::setCustomIO(uint8_t (* readPin) (pin_t pin),
    void (* writePin) (pin_t pin, uint8_t state))
{
  m_readPinFunct = readPin;
  m_writePinFunct = writePin;
}


/**
 * Sets the default button configuration for further added buttons.
 *
 * @param pullup Pullup option
 * @param activeLow Active low option
 */
void UniversalButtons::setDefaultButtonConfig(uint8_t pullup, uint8_t activeLow)
{
  m_defaultPullup = pullup;
  m_defaultActiveLow = activeLow;
}
