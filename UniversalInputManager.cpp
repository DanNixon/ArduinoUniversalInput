#include "UniversalInputManager.h"

#include "ArduinoButton.h"
#include "ArduinoJoystick.h"

UniversalInputManager::UniversalInputManager()
    : m_listHead(NULL)
    , m_callback(NULL)
    , m_defaultActiveLow(true)
    , m_defaultPullUp(true)
    , m_defaultDebounce(10)
{
}

size_t UniversalInputManager::poll()
{
  size_t updatedDevices = 0;
  UIMListNode *item = m_listHead;

  while (item != NULL)
  {
    IInputDevice *device = item->device;

    if (device->poll())
    {
      updatedDevices++;

      if (m_callback)
        m_callback->handleUniversalInputEvent(device->type(), device);
    }

    item = item->next;
  }

  return updatedDevices;
}

bool UniversalInputManager::setCallback(IUniversalInputCallback *callback)
{
  if (callback == NULL)
    return false;

  m_callback = callback;
  return true;
}

bool UniversalInputManager::setCallback(
    UniversalInputCallbackFunctionHandler::UniversalInputCallbackFunction
        callback)
{
  if (callback == NULL)
    return false;

  m_callback = new UniversalInputCallbackFunctionHandler(callback);
  return true;
}

bool UniversalInputManager::addDevice(IInputDevice *device)
{
  if (deviceExists(device->getID()))
    return false;

  UIMListNode *newNode = new UIMListNode();
  newNode->device = device;
  newNode->next = NULL;

  if (m_listHead == NULL)
  {
    m_listHead = newNode;
  }
  else
  {
    UIMListNode *item = m_listHead;
    while (item->next != NULL)
    {
      item = item->next;
    }

    item->next = newNode;
  }

  m_numDevices++;
  return true;
}

IInputDevice *UniversalInputManager::getDevice(inputid_t id)
{
  UIMListNode *item = m_listHead;
  while (item != NULL)
  {
    IInputDevice *device = item->device;

    if (device->getID() == id)
      return device;

    item = item->next;
  }

  return NULL;
}

bool UniversalInputManager::deviceExists(inputid_t id)
{
  return getDevice(id) != NULL;
}

bool UniversalInputManager::setButtonDefaults(bool activeLow, bool pullUp,
                                              inputtime_t debounce)
{
  if (debounce < 0)
    return false;

  m_defaultActiveLow = activeLow;
  m_defaultPullUp = pullUp;
  m_defaultDebounce = debounce;

  return true;
}

bool UniversalInputManager::addNewButton(inputpin_t pin)
{
  return addNewButton(pin, pin);
}

bool UniversalInputManager::addNewButton(inputid_t id, inputpin_t pin)
{
  ArduinoButton *button =
      new ArduinoButton(id, pin, m_defaultActiveLow, m_defaultPullUp);
  button->setDebounceDelay(m_defaultDebounce);
  bool result = addDevice(button);
  if (!result)
    delete button;
  return result;
}

bool UniversalInputManager::addNewJoystick(inputpin_t pin)
{
  return addNewJoystick(pin, pin);
}

bool UniversalInputManager::addNewJoystick(inputid_t id, inputpin_t pin)
{
  ArduinoJoystick *joystick = new ArduinoJoystick(id, pin);
  bool result = addDevice(joystick);
  if (!result)
    delete joystick;
  return result;
}
