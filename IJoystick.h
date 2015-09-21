#ifndef _ARDUINOUNIVERSALINPUTS_IJOYSTICK_H
#define _ARDUINOUNIVERSALINPUTS_IJOYSTICK_H

#include "IInputDevice.h"
#include "IValueTransform.h"

class IJoystick : public IInputDevice
{
public:
  IJoystick(inputid_t id);

  inputtype_t type() { return UIT_JOYSTICK; }

  bool poll();

  inputanalog_t getRawValue() { return m_value; }
  inputanalog_t getCentredValue();
  inputanalog_t getValue();

  void setTransformation(IValueTransform *transform);

  bool setThreshold(inputanalog_t threshold);
  inputanalog_t getThreshold() { return m_threshold; }

  bool setPoints(inputanalog_t low, inputanalog_t centre, inputanalog_t high);
  bool setPoints(inputanalog_t low, inputanalog_t high);
  bool setDeadbands(inputanalog_t low, inputanalog_t centre,
                    inputanalog_t high);
  bool setDeadbands(inputanalog_t low, inputanalog_t high);

  inputanalog_t getLowPoint() { return m_low; }
  inputanalog_t getCentrePoint() { return m_centre; }
  inputanalog_t getHighPoint() { return m_high; }

  inputanalog_t getLowDeadband() { return m_deadbandLow; }
  inputanalog_t getCentreDeadband() { return m_deadbandCentre; }
  inputanalog_t getHighDeadband() { return m_deadbandHigh; }

protected:
  virtual inputanalog_t getPhysicalValue() = 0;

private:
  bool withinTolerance(inputanalog_t a, inputanalog_t b,
                       inputanalog_t tolerance);

  IValueTransform *m_transform;
  inputanalog_t m_threshold;

  inputanalog_t m_value;

  inputanalog_t m_low;
  inputanalog_t m_centre;
  inputanalog_t m_high;

  inputanalog_t m_deadbandLow;
  inputanalog_t m_deadbandCentre;
  inputanalog_t m_deadbandHigh;
};

#endif
