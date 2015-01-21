#include <inttypes.h>
#include <UniversalInput.h>

#include "JoystickTypes.h"


using UniversalInput::Result;


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

    Result setToRangeLow(joystickvalue_t value);
    joystickvalue_t getToRangeLow() { return m_toRangeLow; }

    Result setToRangeHigh(joystickvalue_t value);
    joystickvalue_t getToRangeHigh() { return m_toRangeHigh; }

    Result setFromRangeLow(int32_t value);
    int32_t getFromRangeLow() { return m_fromRangeLow; }

    Result setFromRangeHigh(int32_t value);
    int32_t getFromRangeHigh() { return m_fromRangeHigh; }

    Result setCentrePoint(int32_t value);
    int32_t getCentrePoint() { return m_centrePoint; }

    Result setLowerDeadBandWidth(int32_t value);
    int32_t getLowerDeadBandWidth() { return m_deadBandWidthLow; }

    Result setCentreDeadBandWIdth(int32_t value);
    int32_t getCentreDeadBandWidth() { return m_deadBandWidthCentre; }

    Result setUpperDeadBandWidth(int32_t value);
    int32_t getUpperDeadBandWidth() { return m_deadBandWidthHigh; }

    Result setPolarity(joystickpolaity_t polarity);
    joystickpolaity_t getPolarity() { return m_polarity; }

    Result setDeltaThreshold(joystickvalue_t threshold);
    joystickvalue_t getDeltaThreshold() { return m_deltaThreshold; }


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
