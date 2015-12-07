/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IUNIVERSALINPUTCALLBACK_H
#define _ARDUINOUNIVERSALINPUTS_IUNIVERSALINPUTCALLBACK_H

/*!
 * \class IUniversalInputCallback
 * \brief Interface for classes that handle callbacks.
 */
class IUniversalInputCallback
{
public:
  IUniversalInputCallback() {}

  /*!
   * \brief Handle a calback.
   * \param type Type of input device
   * \param device Pointer to the input device
   */
  virtual void handleUniversalInputEvent(inputtype_t type,
                                         IInputDevice *device) = 0;
};

#endif
