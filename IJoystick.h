/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IJOYSTICK_H
#define _ARDUINOUNIVERSALINPUTS_IJOYSTICK_H

#include "IInputDevice.h"
#include "IValueTransform.h"

/*!
 * \class IJoystick
 * \brief Represents a joystick or potentiometer.
 */
class IJoystick : public IInputDevice
{
public:
  IJoystick(inputid_t id);
  virtual ~IJoystick();

  /*!
   * \copydoc IInputDevice::type
   */
  inputtype_t type() const { return UIT_JOYSTICK; }

  /*!
   * \copydoc IInputDevice::poll
   */
  bool poll();

  /*!
   * \brief Gets last read raw value.
   * \return Raw value
   */
  inputanalog_t getRawValue() const { return m_value; }

  inputanalog_t getCentredValue() const;
  inputanalog_t getValue() const;

  void setTransformation(IValueTransform *transform);

  bool setThreshold(inputanalog_t threshold);

  /*!
   * \brief Returns the threshold value.
   * \return Threshold
   */
  inputanalog_t getThreshold() const { return m_threshold; }

  bool setPoints(inputanalog_t low, inputanalog_t centre, inputanalog_t high);
  bool setPoints(inputanalog_t low, inputanalog_t high);
  bool setDeadbands(inputanalog_t low, inputanalog_t centre,
                    inputanalog_t high);
  bool setDeadbands(inputanalog_t low, inputanalog_t high);

  /*!
   * \brief Gets the low end point raw value.
   * \return Low end point
   */
  inputanalog_t getLowPoint() const { return m_low; }

  /*!
   * \brief Gets the centre point raw value.
   * \return Centre point
   */
  inputanalog_t getCentrePoint() const { return m_centre; }

  /*!
   * \brief Gets the high end point raw value.
   * \return High end point
   */
  inputanalog_t getHighPoint() const { return m_high; }

  /*!
   * \brief Gets the deadband width at the low end point.
   * \return Low deadband width
   */
  inputanalog_t getLowDeadband() const { return m_deadbandLow; }

  /*!
   * \brief Gets the deadband width at the centre point.
   * \return Centre deadband width
   */
  inputanalog_t getCentreDeadband() const { return m_deadbandCentre; }

  /*!
   * \brief Gets the deadband width at the high end point.
   * \return High deadband width
   */
  inputanalog_t getHighDeadband() const { return m_deadbandHigh; }

protected:
  /*!
   * \brief Gets the raw value form the joystick.
   * \return Raw value
   */
  virtual inputanalog_t getPhysicalValue() const = 0;

private:
  bool withinTolerance(inputanalog_t a, inputanalog_t b,
                       inputanalog_t tolerance) const;

  IValueTransform *m_transform; //!< Value thransformation to apply to value
  inputanalog_t
      m_threshold; //!< Threshold change in raw value to fire a callback

  inputanalog_t m_value; //!< Last read raw value

  inputanalog_t m_low;    //!< Low end point (raw value)
  inputanalog_t m_centre; //!< Centre point (raw value)
  inputanalog_t m_high;   //!< High end point (raw value)

  inputanalog_t m_deadbandLow;    //!< Deadband at low end point (raw value)
  inputanalog_t m_deadbandCentre; //!< Deadband at centre point (raw value)
  inputanalog_t m_deadbandHigh;   //!< Deadband at high end point (raw value)
};

#endif
