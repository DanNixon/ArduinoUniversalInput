/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IUNIVERSALINPUTCALLBACK_H
#define _ARDUINOUNIVERSALINPUTS_IUNIVERSALINPUTCALLBACK_H

class IUniversalInputCallback
{
public:
  IUniversalInputCallback() {}

  virtual void handleUniversalInputEvent(inputtype_t type,
                                         IInputDevice *device) = 0;
};

#endif
