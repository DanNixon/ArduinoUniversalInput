#include "JoystickConfig.h"


JoystickConfig::JoystickConfig() :
  m_toRangeHigh(100), m_toRangeLow(-100),

  m_fromRangeHigh(1023), m_fromRangeLow(0),
  m_centrePoint(512),

  m_deadBandWidthHigh(0),
  m_deadBandWidthCentre(0),
  m_deadBandWidthLow(0),

  m_polarity(POLARITY_POSITIVE),

  m_deltaThreshold(5)
{
}


joystickvalue_t JoystickConfig::convertRaw(int32_t value)
{
  //TODO
  return value;
}
