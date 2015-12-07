/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKFUNCTIONHANDLER_H
#define _ARDUINOUNIVERSALINPUTS_UNIVERSALINPUTCALLBACKFUNCTIONHANDLER_H

#include "IUniversalInputCallback.h"

/*!
 * \class UniversalInputCallbackFunctionHandler
 * \brief Callback handler for function pointers.
 */
class UniversalInputCallbackFunctionHandler : public IUniversalInputCallback
{
public:
  /*!
   * \typedef UniversalInputCallbackFunction
   * \brief Callback function pointer type.
   */
  typedef void (*UniversalInputCallbackFunction)(inputtype_t, IInputDevice *);

  /*!
   * \brief Create a new function pointer callback handler.
   * \param func Pointer to the callback function
   */
  UniversalInputCallbackFunctionHandler(UniversalInputCallbackFunction func)
      : IUniversalInputCallback()
      , m_function(func)
  {
  }

  /*!
   * \copydoc IUniversalInputCallback::handleUniversalInputEvent
   *
   * Dispatches the event to the function given in the constructor.
   */
  void handleUniversalInputEvent(inputtype_t type, IInputDevice *device)
  {
    if (m_function != NULL)
      m_function(type, device);
  }

private:
  UniversalInputCallbackFunction m_function; //!< The callback function pointer
};

#endif
