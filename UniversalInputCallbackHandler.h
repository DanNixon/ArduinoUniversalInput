#ifndef _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKHANDLER_H
#define _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKHANDLER_H

#include "IUniversalInputCallback.h"

class UniversalInputCallbackHandler
{
public:
  typedef void (*UniversalInputCallbackFunction)(inputtype_t, IInputDevice *);

  UniversalInputCallbackHandler(IUniversalInputCallback *obj):
    m_object(obj), m_function(NULL)
  {
  }
  
  UniversalInputCallbackHandler(UniversalInputCallbackFunction f):
    m_object(NULL), m_function(f)
  {
  }

  void operator()(inputtype_t type, IInputDevice *device)
  {
    if(m_object == NULL)
      m_function(type, device);
    else
      m_object->handleUniversalInputEvent(type, device);
  }

private:
  IUniversalInputCallback *m_object;
  UniversalInputCallbackFunction m_function;
};

#endif