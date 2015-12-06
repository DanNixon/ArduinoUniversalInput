/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKFUNCTIONHANDLER_H
#define _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKFUNCTIONHANDLER_H

#include "IUniversalInputCallback.h"

class UniversalInputCallbackFunctionHandler : public IUniversalInputCallback
{
public:
  typedef void (*UniversalInputCallbackFunction)(inputtype_t, IInputDevice *);

  UniversalInputCallbackFunctionHandler(UniversalInputCallbackFunction func)
      : IUniversalInputCallback()
      , m_function(func)
  {
  }

  void handleUniversalInputEvent(inputtype_t type, IInputDevice *device)
  {
    if (m_function != NULL)
      m_function(type, device);
  }

private:
  UniversalInputCallbackFunction m_function;
};

#endif
