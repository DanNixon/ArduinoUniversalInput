/*
 * UniversalButtons button input library
 *
 * ArduinoUniversalButtons
 * Dan Nixon, dan-nixon.com
 * 23/06/2014
 */

#include <UniversalButtons.h>

UniversalButtons::UniversalButtons()
{
  _debounceDelay = DEFAULT_DEBOUCE_DELAY;

  _defaultPullup = DEFAULT_PULLUP;
  _defaultActiveLow = DEFAULT_ACTIVE_LOW;

  _readPinFunct = NULL;
  _writePinFunct = NULL;

  _callback = NULL;

  _buttonList = NULL;
  _buttonCount = 0;
}

UniversalButtons::~UniversalButtons()
{
  delete _buttonList;
}

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

void UniversalButtons::poll()
{
  uint8_t buttonState;
  Button *ptr = _buttonList;

  while(ptr)
  {
    if((millis() - ptr->lastEdgeTime) > _debounceDelay)
    {
      buttonState = readButtonState(ptr);

      if(buttonState != ptr->lastState)
      {
        ptr->lastEdgeTime = millis();

        if(_callback)
          _callback(ptr->id, buttonState);
      }

      ptr->lastState = buttonState;
    }

    ptr = ptr->next;
  }
}

void UniversalButtons::setCallback(void (* callback) (buttonid_t bid, uint8_t state))
{
  _callback = callback;
}

void UniversalButtons::buttonListAppend(Button *button)
{
  if(!_buttonList)
  {
    _buttonList = button;
  }
  else
  {
    Button *ptr = _buttonList;

    while(ptr->next)
    {
      ptr = ptr->next;
    }

    ptr->next = button;
  }

  _buttonCount++;
}

Result UniversalButtons::addButton(buttonid_t bid, pin_t pin, uint8_t pullup, uint8_t activeLow)
{
  Button *newButton = new Button;
  newButton->type = TYPE_GPIO_BASIC;
  newButton->id = bid;
  newButton->rowPin = pin;
  newButton->columnPin = -1;
  newButton->pinRead = (uint8_t (*) (pin_t)) &digitalRead;
  newButton->pinWrite = NULL;
  newButton->activeLow = activeLow;
  newButton->next = NULL;

  pinMode(pin, INPUT);
  if(pullup)
  {
    digitalWrite(pin, HIGH);
  }

  buttonListAppend(newButton);

  return RESULT_OK;
}

Result UniversalButtons::addButton(buttonid_t bid, pin_t pin)
{
  return addButton(bid, pin, _defaultPullup, _defaultActiveLow);
}

Result UniversalButtons::addButton(buttonid_t bid, pin_t rowPin, pin_t colPin)
{
  Button *newButton = new Button;
  newButton->type = TYPE_GPIO_MATRIX;
  newButton->id = bid;
  newButton->rowPin = rowPin;
  newButton->columnPin = colPin;
  newButton->pinRead = (uint8_t (*) (pin_t)) &digitalRead;
  newButton->pinWrite = &digitalWrite;
  newButton->activeLow = 0;
  newButton->next = NULL;

  pinMode(rowPin, INPUT);
  pinMode(colPin, OUTPUT);

  digitalWrite(rowPin, HIGH);
  digitalWrite(colPin, HIGH);

  buttonListAppend(newButton);

  return RESULT_OK;
}

Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t pin, uint8_t pullup, uint8_t activeLow)
{
  if(!(_readPinFunct && _writePinFunct))
    return RESULT_NO_CUSTOM_IO;

  Button *newButton = new Button;
  newButton->type = TYPE_CUSTOM_BASIC;
  newButton->id = bid;
  newButton->rowPin = pin;
  newButton->columnPin = -1;
  newButton->pinRead = _readPinFunct;
  newButton->pinWrite = _writePinFunct;
  newButton->activeLow = activeLow;
  newButton->next = NULL;
 
  if(pullup)
  {
    _writePinFunct(pin, 1);
  }

  buttonListAppend(newButton);

  return RESULT_OK;
}

Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t pin)
{
  return addCustomButton(bid, pin, _defaultPullup, _defaultActiveLow);
}

Result UniversalButtons::addCustomButton(buttonid_t bid, pin_t rowPin, pin_t colPin)
{
  if(!( _readPinFunct && _writePinFunct))
    return RESULT_NO_CUSTOM_IO;

  Button *newButton = new Button;
  newButton->type = TYPE_CUSTOM_MATRIX;
  newButton->id = bid;
  newButton->rowPin = rowPin;
  newButton->columnPin = colPin;
  newButton->pinRead = _readPinFunct;
  newButton->pinWrite = _writePinFunct;
  newButton->activeLow = 0;
  newButton->next = NULL;

  buttonListAppend(newButton);

  return RESULT_OK;
}

Result UniversalButtons::removeButton(buttonid_t bid)
{
  if(_buttonCount == 0)
  {
    return RESULT_NO_SUCH_BUTTON;
  }
  if(_buttonCount == 1)
  {
    if(_buttonList->id == bid)
    {
      delete _buttonList;
      _buttonCount--;

      return RESULT_OK;
    }
  }
  else
  {
    Button *prev = NULL;
    Button *current = _buttonList;

    while(current)
    {

      if(current->id == bid)
      {
        if(current->next)
        {
          if(prev)
            prev->next = current->next;
          else
            _buttonList = current->next;
        }

        delete current;

        return RESULT_OK;
      }

      prev = current;
      current = current->next;
    }
  }
 
  return RESULT_NO_SUCH_BUTTON;
}

uint16_t UniversalButtons::getDebounceDelay()
{
  return _debounceDelay;
}

void UniversalButtons::setDebounceDelay(uint16_t delay)
{
  _debounceDelay = delay;
}

int8_t UniversalButtons::getButtonState(buttonid_t bid)
{
  Button *ptr = _buttonList;
  
  while(ptr)
  {
    if(ptr->id == bid)
      return ptr->lastState;

    ptr = ptr->next;
  }

  return -1;
}

uint16_t UniversalButtons::buttonCount()
{
  return _buttonCount;
}

void UniversalButtons::setCustomIO(uint8_t (* readPin) (pin_t pin),
    void (* writePin) (pin_t pin, uint8_t state))
{
  _readPinFunct = readPin;
  _writePinFunct = writePin;
}

void UniversalButtons::setDefaultButtonConfig(uint8_t pullup, uint8_t activeLow)
{
  _defaultPullup = pullup;
  _defaultActiveLow = activeLow;
}
