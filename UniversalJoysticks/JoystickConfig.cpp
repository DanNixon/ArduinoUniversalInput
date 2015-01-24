#include "JoystickConfig.h"


using namespace UniversalInput;


/**
 * Constructor with reasonable default values.
 */
JoystickConfig::JoystickConfig() :
  m_toRangeHigh(100),
  m_toRangeLow(-100),

  m_fromHigh(1023),
  m_fromCentre(512),
  m_fromLow(0),

  m_deadBandHigh(0),
  m_deadBandCentre(0),
  m_deadBandLow(0),

  m_polarity(POLARITY_POSITIVE),
  m_hasCentrePoint(false),

  m_deltaThreshold(5)
{
}


/**
 * Constructor with configurable values.
 */
JoystickConfig::JoystickConfig(joystickvalue_t toLow, joystickvalue_t toHigh,
                               joystickraw_t fromLow, joystickraw_t fromCentre, joystickraw_t fromHigh,
                               joystickraw_t deadBandLow, joystickraw_t deadBandCentre, joystickraw_t deadBandHigh,
                               joystickpolaity_t polarity, bool hasCentrePoint,
                               joystickvalue_t deltaThreshold) :
  m_toRangeHigh(INT32_MAX),
  m_toRangeLow(INT32_MIN),

  m_fromHigh(INT32_MAX),
  m_fromCentre(0),
  m_fromLow(INT32_MIN),

  m_deadBandHigh(0),
  m_deadBandCentre(0),
  m_deadBandLow(0),

  m_polarity(POLARITY_POSITIVE),
  m_hasCentrePoint(false),

  m_deltaThreshold(0)
{
  setToRangeLow(toLow);
  setToRangeHigh(toHigh);

  setFromCentre(fromCentre);
  setFromLow(fromLow);
  setFromHigh(fromHigh);

  setDeadBandLow(deadBandLow);
  setDeadBandCentre(deadBandCentre);
  setDeadBandHigh(deadBandHigh);

  setPolarity(polarity);
  setHasCentrePoint(hasCentrePoint);

  setDeltaThreshold(deltaThreshold);
}


/**
 * Converts a raw value from the ADC to a sensible value in the output range defined.
 *
 * @param value Raw ADC value
 * @return Converted value
 */
joystickvalue_t JoystickConfig::convertRaw(joystickraw_t value)
{
  // Get map to range based on polarity
  joystickvalue_t toLow = (m_polarity == POLARITY_POSITIVE) ? m_toRangeLow : m_toRangeHigh;
  joystickvalue_t toHigh = (m_polarity == POLARITY_POSITIVE) ? m_toRangeHigh : m_toRangeLow;
  joystickvalue_t toCentre = ((toHigh - toLow) / 2) + toLow;

  // Handle lower dead band case
  if(withinTolRange(value, m_fromLow, m_deadBandLow))
    return toLow;

  // Handle upper dead band case
  if(withinTolRange(value, m_fromHigh, m_deadBandHigh))
    return toHigh;

  // Handle centre dead band case
  if(withinTolRange(value, m_fromCentre, m_deadBandCentre) && m_hasCentrePoint)
    return toCentre;

  // Handle the mapping on the appropriate side of the centre point
  bool positiveSide = (value >= m_fromCentre);
  joystickraw_t fromLow = m_fromLow;
  joystickraw_t fromHigh = m_fromHigh;

  if(m_hasCentrePoint)
  {
    if(positiveSide)
    {
      toLow = toCentre;
      fromLow = m_fromCentre;
    }
    else
    {
      toHigh = toCentre;
      fromHigh = m_fromCentre;
    }
  }


  joystickvalue_t mapped = (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;

  return mapped;
}


/**
 * CHecks to see if  value is in range of another using a dead band
 * with a given width.
 *
 * @param testValue Value to check
 * @param pointValue Value of the reference point
 * @param tolerance Dead band width
 * @return True if value is in dead band range
 */
bool JoystickConfig::withinTolRange(joystickraw_t testValue, joystickraw_t pointValue, joystickraw_t tolerance)
{
  joystickraw_t error = tolerance / 2;
  joystickraw_t limUpper = pointValue  + error;
  joystickraw_t limLower = pointValue  - error;
  return (testValue <= limUpper && testValue >= limLower);
}


/**
 * Sets the lower end of the range of target mapped values for the joystick position.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setToRangeLow(joystickvalue_t value)
{
  if(value >= getToRangeHigh())
    return RESULT_OUT_OF_RANGE;

  m_toRangeLow = value;
  return RESULT_OK;
}


/**
 * Sets the upper end of the range of target mapped values for the joystick position.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setToRangeHigh(joystickvalue_t value)
{
  if(value <= getToRangeLow())
    return RESULT_OUT_OF_RANGE;

  m_toRangeHigh = value;
  return RESULT_OK;
}


/**
 * Sets the lower end of the range of original mapped values for the raw ADC values.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setFromLow(joystickraw_t value)
{
  if(value >= getFromHigh())
    return RESULT_OUT_OF_RANGE;

  m_fromLow = value;
  return RESULT_OK;
}


/**
 * Sets the centre point of the range of original mapped values for the raw ADC values.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setFromCentre(joystickraw_t value)
{
  if(value < getFromLow() || value > getFromHigh())
    return RESULT_OUT_OF_RANGE;

  m_fromCentre = value;
  return RESULT_OK;
}


/**
 * Sets the upper end of the range of original mapped values for the raw ADC value.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setFromHigh(joystickraw_t value)
{
  if(value <= getFromLow())
    return RESULT_OUT_OF_RANGE;

  m_fromHigh = value;
  return RESULT_OK;
}


/**
 * Sets the width of the dead band at the lower end of the raw ADC values range.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setDeadBandLow(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandLow = value;
  return RESULT_OK;
}


/**
 * Sets the width of the dead band at the centre point of the raw ADC values range.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setDeadBandCentre(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandCentre = value;
  return RESULT_OK;
}


/**
 * Sets the width of the dead band at the upper end of the raw ADC values range.
 *
 * @param value Value to set
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setDeadBandHigh(joystickraw_t value)
{
  if(value <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deadBandHigh = value;
  return RESULT_OK;
}


/**
 * Sets the polarity of the joystick.
 * An easy way to invert the range of output values.
 *
 * @param polarity New polarity
 * @return Always RESULT_OK
 */
Result JoystickConfig::setPolarity(joystickpolaity_t polarity)
{
  m_polarity = polarity;
  return RESULT_OK;
}


/**
 * Sets if this joystick has a centre point.
 *
 * @param hasCentrePoint If there is a centre point
 * @return Always RESULT_OK
 */
Result JoystickConfig::setHasCentrePoint(bool hasCentrePoint)
{
  m_hasCentrePoint = hasCentrePoint;
  return RESULT_OK;
}


/**
 * Sets the threshold at which the position is deemed to have changed.
 *
 * @param threshold Threshold in mapped to range.
 * @return If the value was set, otherwise the error in setting the value
 */
Result JoystickConfig::setDeltaThreshold(joystickvalue_t threshold)
{
  if(threshold <= 0)
    return RESULT_OUT_OF_RANGE;

  m_deltaThreshold = threshold;
  return RESULT_OK;
}
