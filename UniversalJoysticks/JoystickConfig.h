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

    JoystickConfig(joystickvalue_t toLow, joystickvalue_t toHigh,
                   joystickraw_t fromLow, joystickraw_t fromCentre, joystickraw_t fromHigh,
                   joystickraw_t deadBandLow, joystickraw_t deadBandCentre, joystickraw_t deadBandHigh,
                   joystickpolaity_t polarity, bool hasCentrePoint,
                   joystickvalue_t deltaThreshold);

    joystickvalue_t convertRaw(joystickraw_t value);
    bool withinTolRange(joystickraw_t testValue, joystickraw_t pointValue, joystickraw_t tolerance);

    Result setToRangeLow(joystickvalue_t value);
    joystickvalue_t getToRangeLow() { return m_toRangeLow; }

    Result setToRangeHigh(joystickvalue_t value);
    joystickvalue_t getToRangeHigh() { return m_toRangeHigh; }

    Result setFromLow(joystickraw_t value);
    joystickraw_t getFromLow() { return m_fromLow; }

    Result setFromCentre(joystickraw_t value);
    joystickraw_t getFromCentre() { return m_fromCentre; }

    Result setFromHigh(joystickraw_t value);
    joystickraw_t getFromHigh() { return m_fromHigh; }

    Result setDeadBandLow(joystickraw_t value);
    joystickraw_t getDeadBandLow() { return m_deadBandLow; }

    Result setDeadBandCentre(joystickraw_t value);
    joystickraw_t getDeadBandCentre() { return m_deadBandCentre; }

    Result setDeadBandHigh(joystickraw_t value);
    joystickraw_t getDeadBandHigh() { return m_deadBandHigh; }

    Result setPolarity(joystickpolaity_t polarity);
    joystickpolaity_t getPolarity() { return m_polarity; }

    Result setHasCentrePoint(bool hasCentrePoint);
    bool getHasCentrePoint() { return m_hasCentrePoint; }

    Result setDeltaThreshold(joystickvalue_t threshold);
    joystickvalue_t getDeltaThreshold() { return m_deltaThreshold; }


  private:
    joystickvalue_t m_toRangeHigh;
    joystickvalue_t m_toRangeLow;

    joystickraw_t m_fromHigh;
    joystickraw_t m_fromCentre;
    joystickraw_t m_fromLow;

    joystickraw_t m_deadBandHigh;
    joystickraw_t m_deadBandCentre;
    joystickraw_t m_deadBandLow;

    joystickpolaity_t m_polarity;
    bool m_hasCentrePoint;

    joystickvalue_t m_deltaThreshold;

};
