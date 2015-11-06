#ifndef _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H
#define _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H

#include "UniversalInputTypes.h"

class IValueTransform
{
public:
  IValueTransform(inputanalog_t fromLow, inputanalog_t fromHigh)
      : m_fromLow(fromLow)
      , m_fromHigh(fromHigh)
  {
  }

  virtual ~IValueTransform()
  {
  };

  virtual inputanalog_t transform(inputanalog_t raw) = 0;

protected:
  inputanalog_t m_fromLow;
  inputanalog_t m_fromHigh;
};

#endif
