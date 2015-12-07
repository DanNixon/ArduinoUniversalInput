/*! \file */

#include "UniversalInputManager.h"

#include "ArduinoButton.h"
#include "ArduinoJoystick.h"

/*!
 * \brief Create a new input manager.
 */
UniversalInputManager::UniversalInputManager()
    : m_listHead(NULL)
    , m_callback(NULL)
    , m_defaultActiveLow(true)
    , m_defaultPullUp(true)
    , m_defaultDebounce(10)
{
}

/*!
 * \brief Polls all input devices for change.
 * \return Number of devices with changed state
 */
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

/*!
 * \brief Sets the callback class for this manager.
 * \param callback Pointer to the callback handler
 * \return True if the callback was set
 */
bool UniversalInputManager::setCallback(IUniversalInputCallback *callback)
{
  if (callback == NULL)
    return false;

  m_callback = callback;
  return true;
}

/*!
 * \brief Sets the callback function for this manager.
 * \param callback Pointer to the callback function
 * \return True if the callback was set
 */
bool UniversalInputManager::setCallback(
    UniversalInputCallbackFunctionHandler::UniversalInputCallbackFunction
        callback)
{
  if (callback == NULL)
    return false;

  m_callback = new UniversalInputCallbackFunctionHandler(callback);
  return true;
}

/*!
 * \brief Adds a new input device to the manager.
 * \param device Pointer to input device
 * \return True if device was added
 *
 * Note that the device ID must be unique, if a device with the same ID already
 * exists this call will return false.
 */
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

/*!
 * \brief Gets an input device given its ID.
 * \param id Device ID
 * \return Pointer to input device, NULL if not found
 */
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

/*!
 * \brief Determines if a given device ID exists in the manager.
 * \param id ID of device
 * \return True if device exists in this manager
 */
bool UniversalInputManager::deviceExists(inputid_t id)
{
  return getDevice(id) != NULL;
}

/*!
 * \brief Sets the default button configuraton for buttons created with
 *        UniversalInputManager::addNewButton.
 * \param activeLow True if active low by default
 * \param pullUp True of pull up by default
 * \param debounce Default debounce time
 * \return True if all values are valid and have been set
 * \see UniversalInputManager::addNewButton(inputpin_t)
 * \see UniversalInputManager::addNewButton(inputid_t, inputpin_t)
 */
bool UniversalInputManager::setButtonDefaults(bool activeLow, bool pullUp,
                                              inputtime_t debounce)
{
  if (debounce <= 0)
    return false;

  m_defaultActiveLow = activeLow;
  m_defaultPullUp = pullUp;
  m_defaultDebounce = debounce;

  return true;
}

/*!
 * \brief Adds a new button with default configuration.
 * \param pin Pin button is attached to
 * \return True if button was added
 * \see UniversalInputManager::setButtonDefaults
 * \see UniversalInputManager::addNewButton(inputid_t, inputpin_t)
 *
 * Note that pin number becomes device ID.
 */
bool UniversalInputManager::addNewButton(inputpin_t pin)
{
  return addNewButton(pin, pin);
}

/*!
 * \brief Adds a new button with default configuration.
 * \param id ID of new button
 * \param pin Pin button is attached to
 * \return True if button was added
 * \see UniversalInputManager::setButtonDefaults
 * \see UniversalInputManager::addNewButton(inputpin_t)
 */
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

/*!
 * \brief Adds a new joystick.
 * \param pin Pin joystick is attached to
 * \return True if joystick was added
 * \see UniversalInputManager::addNewJoystick(inputid_t, inputpin_t)
 *
 * Note that pin number becomes device ID.
 */
bool UniversalInputManager::addNewJoystick(inputpin_t pin)
{
  return addNewJoystick(pin, pin);
}

/*!
 * \brief Adds a new joystick.
 * \param id ID of new joystick
 * \param pin Pin joystick is attached to
 * \return True if joystick was added
 * \see UniversalInputManager::addNewJoystick(inputpin_t)
 */
bool UniversalInputManager::addNewJoystick(inputid_t id, inputpin_t pin)
{
  ArduinoJoystick *joystick = new ArduinoJoystick(id, pin);
  bool result = addDevice(joystick);
  if (!result)
    delete joystick;
  return result;
}
