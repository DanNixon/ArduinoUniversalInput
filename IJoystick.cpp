#include "IJoystick.h"

#include "Arduino.h"

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

inputanalog_t IJoystick::getCentredValue()
{
  inputanalog_t value = getRawValue();

  // Handle deadbands
  if (withinTolerance(value, m_high, m_deadbandHigh))
    value = m_high;
  else if (withinTolerance(value, m_centre, m_deadbandCentre))
    value = m_centre;
  else if (withinTolerance(value, m_low, m_deadbandLow))
    value = m_low;

  // Centre value about zero
  value -= m_centre;

  return value;
}

inputanalog_t IJoystick::getValue()
{
  inputanalog_t value = getCentredValue();

  if (m_transform != NULL)
    value = m_transform->transform(value);

  return value;
}

void IJoystick::setTransformation(IValueTransform *transform)
{
  m_transform = transform;
}

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

bool IJoystick::setPoints(inputanalog_t low, inputanalog_t high)
{
  return setPoints(low, low, high);
}

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

bool IJoystick::setDeadbands(inputanalog_t low, inputanalog_t high)
{
  return setDeadbands(low, low, high);
}

bool IJoystick::setThreshold(inputanalog_t threshold)
{
  if (threshold < 0)
    return false;

  m_threshold = threshold;
  return true;
}

bool IJoystick::withinTolerance(inputanalog_t a, inputanalog_t b,
                                inputanalog_t tolerance)
{
  return (abs(a - b) < tolerance);
}
