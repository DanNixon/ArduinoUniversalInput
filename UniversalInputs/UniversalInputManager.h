#ifndef _ARDUINOUNIVERSALINPUTS_INPUTMANAGER_H
#define _ARDUINOUNIVERSALINPUTS_INPUTMANAGER_H

#include "Types.h"
#include "IInputDevice.h"


typedef void (* inputcallback_t)(UniversalInputType, IInputDevice *);


struct UIMListNode
{
  UIMListNode * next;
  IInputDevice * device;
};


class UniversalInputManager
{
  public:
    UniversalInputManager();

    size_t deviceCount() { return m_numDevices; }

    size_t poll();
    void setCallback(inputcallback_t callback);
    bool addDevice(IInputDevice * device);

  private:
    size_t m_numDevices;
    UIMListNode * m_listHead;
    inputcallback_t m_callback;
};

#endif
