#ifndef _ARDUINOUNIVERSALINPUTS_IBUTTON_H
#define _ARDUINOUNIVERSALINPUTS_IBUTTON_H

#include "IInputDevice.h"

class IButton : public IInputDevice
{
  public:
    IButton(inputid_t id) : IInputDevice(id) {}

    virtual bool isActive();
    virtual inputtime_t lastStateChange();
    virtual inputtime_t lastAciveTime();
};

#endif
