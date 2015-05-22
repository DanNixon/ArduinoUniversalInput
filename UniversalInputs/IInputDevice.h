#ifndef _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H
#define _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H

#include "Types.h"

class IInputDevice
{
  public:
    IInputDevice(inputid_t id) : m_id(id) {}

    inputid_t getID() { return m_id; }

    virtual UniversalInputType type() = 0;
    virtual bool poll() = 0;

  private:
    inputid_t m_id;

};

#endif
