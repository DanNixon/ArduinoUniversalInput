/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_INPUTMANAGER_H
#define _ARDUINOUNIVERSALINPUTS_INPUTMANAGER_H

#include "UniversalInputTypes.h"
#include "IInputDevice.h"
#include "UniversalInputCallbackFunctionHandler.h"

/*!
 * \struct UIMListNode
 * \brief Node type for linked list of IInputDevice.
 */
struct UIMListNode
{
  UIMListNode *next; //!< Pointer to next node
  IInputDevice *device; //!< Pointer to input device
};

/*!
 * \class UniversalInputManager
 * \brief Handles the storage, polling and event handling for multiple input
 *        devices.
 */
class UniversalInputManager
{
public:
  UniversalInputManager();

  size_t deviceCount() { return m_numDevices; }

  size_t poll();

  bool setCallback(IUniversalInputCallback *callback);
  bool setCallback(
      UniversalInputCallbackFunctionHandler::UniversalInputCallbackFunction
          callback);

  bool addDevice(IInputDevice *device);
  IInputDevice *getDevice(inputid_t id);
  bool deviceExists(inputid_t id);

  // ArduinoButton functions
  bool setButtonDefaults(bool activeLow, bool pullUp, inputtime_t debounce);
  bool addNewButton(inputpin_t pin);
  bool addNewButton(inputid_t id, inputpin_t pin);

  // ArduinoJoystick functions
  bool addNewJoystick(inputpin_t pin);
  bool addNewJoystick(inputid_t id, inputpin_t pin);

private:
  size_t m_numDevices;
  UIMListNode *m_listHead;
  IUniversalInputCallback *m_callback;

  bool m_defaultActiveLow;
  bool m_defaultPullUp;
  inputtime_t m_defaultDebounce;
};

#endif
