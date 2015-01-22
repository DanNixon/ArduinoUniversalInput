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

    joystickvalue_t convertRaw(joystickraw_t value);

    Result setToRangeLow(joystickvalue_t value);
    joystickvalue_t getToRangeLow() { return m_toRangeLow; }

    Result setToRangeHigh(joystickvalue_t value);
    joystickvalue_t getToRangeHigh() { return m_toRangeHigh; }

    Result setFromRangeLow(joystickraw_t value);
    joystickraw_t getFromRangeLow() { return m_fromRangeLow; }

    Result setFromRangeHigh(joystickraw_t value);
    joystickraw_t getFromRangeHigh() { return m_fromRangeHigh; }

    Result setCentrePoint(joystickraw_t value);
    joystickraw_t getCentrePoint() { return m_centrePoint; }

    Result setLowerDeadBandWidth(joystickraw_t value);
    joystickraw_t getLowerDeadBandWidth() { return m_deadBandWidthLow; }

    Result setCentreDeadBandWIdth(joystickraw_t value);
    joystickraw_t getCentreDeadBandWidth() { return m_deadBandWidthCentre; }

    Result setUpperDeadBandWidth(joystickraw_t value);
    joystickraw_t getUpperDeadBandWidth() { return m_deadBandWidthHigh; }

    Result setPolarity(joystickpolaity_t polarity);
    joystickpolaity_t getPolarity() { return m_polarity; }

    Result setDeltaThreshold(joystickvalue_t threshold);
    joystickvalue_t getDeltaThreshold() { return m_deltaThreshold; }


  private:
    joystickvalue_t m_toRangeHigh;
    joystickvalue_t m_toRangeLow;

    joystickraw_t m_fromRangeHigh;
    joystickraw_t m_fromRangeLow;

    joystickraw_t m_centrePoint;

    joystickraw_t m_deadBandWidthHigh;
    joystickraw_t m_deadBandWidthCentre;
    joystickraw_t m_deadBandWidthLow;

    joystickpolaity_t m_polarity;

    joystickvalue_t m_deltaThreshold;

};
