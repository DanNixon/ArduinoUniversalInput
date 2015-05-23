#ifndef _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H
#define _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H

#include "Types.h"

class IValueTransform
{
  public:
    virtual inputanalog_t transform(inputanalog_t raw) = 0;
};

#endif
