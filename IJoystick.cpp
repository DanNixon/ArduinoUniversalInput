/*! \file */

#include "IJoystick.h"

#include "Arduino.h"

/*!
 * \brief Creates a new joystick.
 * \param id Joystick ID
 */
IJoystick::IJoystick(inputid_t id)
    : IInputDevice(id)
    , m_transform(NULL)
    , m_threshold(5)
    , m_value(0)
{
  setPoints(-50, 0, 50);
  setDeadbands(0, 0, 0);
}

IJoystick::~IJoystick()
{
}

bool IJoystick::poll()
{
  inputanalog_t value = getPhysicalValue();

  if (!withinTolerance(value, m_value, m_threshold))
  {
    m_value = value;
    return true;
  }

  return false;
}

/*!
 * \brief Gets the value centered at zero at the centre point and clamped if
 *        within the deadbands.
 * \return Centered value
 * \see IJoystick::getRawValue
 * \see IJoystick::getValue
 */
inputanalog_t IJoystick::getCentredValue()
{
  inputanalog_t value = getRawValue();

  /* Handle deadbands */
  if (withinTolerance(value, m_high, m_deadbandHigh))
    value = m_high;
  else if (withinTolerance(value, m_centre, m_deadbandCentre))
    value = m_centre;
  else if (withinTolerance(value, m_low, m_deadbandLow))
    value = m_low;

  /* Centre value about zero */
  value -= m_centre;

  return value;
}

/*!
 * \brief Gets the transformed value.
 * \return Output value
 * \see IJoystick::getCenteredValue
 * \see IJoystick::setTransformation
 *
 * This is the value of IJoystick::getCentredValue with the transformation set
 * by IJoystick::setTransformation applied.
 */
inputanalog_t IJoystick::getValue()
{
  inputanalog_t value = getCentredValue();

  if (m_transform != NULL)
    value = m_transform->transform(value);

  return value;
}

/*!
 * \brief Sets the transformation to use between the centred value and outout
 *        value.
 * \param transform Pointer to the transformation
 */
void IJoystick::setTransformation(IValueTransform *transform)
{
  m_transform = transform;
}

/*!
 * \brief Sets the low, centre and high points.
 * \param low Low end point (raw value)
 * \param centre Centre point (raw value)
 * \param high High end point (raw value)
 * \return True if value are valid and were set
 * \see IJoystick::setPoints(inputanalog_t, inputanalog_t)
 *
 * low <= centre <= high must hold for values to be valid.
 */
bool IJoystick::setPoints(inputanalog_t low, inputanalog_t centre,
                          inputanalog_t high)
{
  if ((low > centre) || (centre > high))
    return false;

  m_low = low;
  m_centre = centre;
  m_high = high;

  return true;
}

/*!
 * \brief Sets the low and high end points.
 * \param low Low end point (raw value)
 * \param high High end point (raw value)
 * \return True if value are valid and were set
 * \see IJoystick::setPoints(inputanalog_t, inputanalog_t, inputanalog_t)
 *
 * For use with potentiometers without a "centre" position.
 *
 * low <= high must hold for values to be valid.
 */
bool IJoystick::setPoints(inputanalog_t low, inputanalog_t high)
{
  return setPoints(low, low, high);
}

/*!
 * \brief Sets the low, centre and high deadband widths.
 * \param low Low deadband width (raw value)
 * \param centre Centre deadband width (raw value)
 * \param high High deadband width (raw value)
 * \return True of all widths are valid and were set
 * \see IJoystick::setDeadbands(inputanalog_t, inputanalog_t)
 */
bool IJoystick::setDeadbands(inputanalog_t low, inputanalog_t centre,
                             inputanalog_t high)
{
  if ((low < 0) || (centre < 0) || (high < 0))
    return false;

  m_deadbandLow = low;
  m_deadbandCentre = centre;
  m_deadbandHigh = high;

  return true;
}

/*!
 * \brief Sets the low and high deadband widths.
 * \param low Low deadband width (raw value)
 * \param high High deadband width (raw value)
 * \return True of all widths are valid and were set
 * \see IJoystick::setDeadbands(inputanalog_t, inputanalog_t, inputanalog_t)
 *
 * For use with potentiometers without a "centre" position.
 */
bool IJoystick::setDeadbands(inputanalog_t low, inputanalog_t high)
{
  return setDeadbands(low, low, high);
}

/*!
 * \brief Sets the minimum change in raw value that will fire an event.
 * \param threshold Threshold value
 * \return True of the value is valid and was set
 */
bool IJoystick::setThreshold(inputanalog_t threshold)
{
  if (threshold < 0)
    return false;

  m_threshold = threshold;
  return true;
}

/*!
 * \brief Determines if two values are within a tolerance of each other.
 * \param a First value
 * \param b Second value
 * \param tolerance Tolerance
 * \return True if a is within tolerance of b
 *
 * Returns true if abs(a - b) < tolerance
 */
bool IJoystick::withinTolerance(inputanalog_t a, inputanalog_t b,
                                inputanalog_t tolerance)
{
  return (abs(a - b) < tolerance);
}
