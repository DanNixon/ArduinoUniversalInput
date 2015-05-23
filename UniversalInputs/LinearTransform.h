#ifndef _ARDUINOUNIVERSALINPUTS_LINEARVALUETRANSFORM_H
#define _ARDUINOUNIVERSALINPUTS_LINEARVALUETRANSFORM_H

#include "IValueTransform.h"


class LinearTransform : public IValueTransform
{
  public:
    LinearTransform(inputanalog_t fromLow, inputanalog_t fromHigh,
                    inputanalog_t toLow, inputanalog_t toHigh) :
      IValueTransform(fromLow, fromHigh),
      m_toLow(toLow), m_toHigh(toHigh)
    {}

    inputanalog_t transform(inputanalog_t raw)
    {
      if(raw == 0)
        return 0;

      return (raw - m_fromLow) * (m_toHigh - m_toLow) / (m_fromHigh - m_fromLow) + m_toLow;
    }

  private:
    inputanalog_t m_toLow;
    inputanalog_t m_toHigh;

};

#endif
