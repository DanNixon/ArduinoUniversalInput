#ifndef _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H
#define _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H

class IInputDevice
{
  public:
    IInputDevice(inputid_t id) : m_id(id) {}

    inputid_t getID() { return m_id; }
    virtual void poll() = 0;

  private:
    m_inputID m_id;

};

#endif
