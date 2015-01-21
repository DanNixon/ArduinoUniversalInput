#include <inttypes.h>

#include "JoystickTypes.h"


enum joystickpolaity_t
{
  POLARITY_POSITIVE,
  POLARITY_NEGATIVE
};


class JoystickConfig
{
  public:
    JoystickConfig();

    joystickvalue_t convertRaw(int32_t value);


  private:
    joystickvalue_t m_toRangeHigh;
    joystickvalue_t m_toRangeLow;

    int32_t m_fromRangeHigh;
    int32_t m_fromRangeLow;

    int32_t m_centrePoint;

    int32_t m_deadBandWidthHigh;
    int32_t m_deadBandWidthCentre;
    int32_t m_deadBandWidthLow;

    joystickpolaity_t m_polarity;

    joystickvalue_t m_deltaThreshold;

};
