#include "JoystickConfig.h"


using namespace UniversalInput;


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


joystickvalue_t JoystickConfig::convertRaw(joystickraw_t value)
{
  //TODO
  return value;
}


Result JoystickConfig::setToRangeLow(joystickvalue_t value)
{
  if(value >= getToRangeHigh())
    return RESULT_OUT_OF_RANGE;

  m_fromRangeLow = value;
  return RESULT_OK;
}


Result JoystickConfig::setToRangeHigh(joystickvalue_t value)
{
  if(value <= getToRangeLow())
    return RESULT_OUT_OF_RANGE;

  m_toRangeHigh = value;
  return RESULT_OK;
}


Result JoystickConfig::setFromRangeLow(joystickraw_t value)
{
  if(value >= getFromRangeHigh())
    return RESULT_OUT_OF_RANGE;

  m_fromRangeLow = value;
  return RESULT_OK;
}


Result JoystickConfig::setFromRangeHigh(joystickraw_t value)
{
  if(value <= getFromRangeLow())
    return RESULT_OUT_OF_RANGE;

  m_fromRangeHigh = value;
  return RESULT_OK;
}


Result JoystickConfig::setCentrePoint(joystickraw_t value)
{
  if(value < getFromRangeLow() || value > getFromRangeHigh())
    return RESULT_OUT_OF_RANGE;

  m_centrePoint = value;
  return RESULT_OK;
}


Result JoystickConfig::setLowerDeadBandWidth(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandWidthLow = value;
  return RESULT_OK;
}


Result JoystickConfig::setCentreDeadBandWIdth(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandWidthCentre = value;
  return RESULT_OK;
}


Result JoystickConfig::setUpperDeadBandWidth(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandWidthHigh = value;
  return RESULT_OK;
}


Result JoystickConfig::setPolarity(joystickpolaity_t polarity)
{
  m_polarity = polarity;
  return RESULT_OK;
}


Result JoystickConfig::setDeltaThreshold(joystickvalue_t threshold)
{
  if(threshold <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deltaThreshold = threshold;
  return RESULT_OK;
}
