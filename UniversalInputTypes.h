/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_TYPES_H
#define _ARDUINOUNIVERSALINPUTS_TYPES_H

#include <Arduino.h>
#include <inttypes.h>

/*!
 * \typedef inputid_t
 * \brief Holds the value of a device ID.
 */
typedef uint16_t inputid_t;

/*!
 * \typedef inputpin_t
 * \brief Holds the value of a pin number.
 */
typedef uint8_t inputpin_t;

/*!
 * \typedef inputtime_t
 * \brief Holds the value of a timestap.
 */
typedef uint32_t inputtime_t;

/*!
 * \typedef inputanalog_t
 * \brief Holds the value of an analog input value.
 */
typedef int32_t inputanalog_t;

/*!
 * \enum inputtype_t
 * \brief Enumeration of all input device types.
 */
enum inputtype_t
{
  UIT_BUTTON, //!< Buttons inheriting from IButton
  UIT_JOYSTICK, //!< Joysticks inheriting from IJoystick
  UIT_ENCODER //!< Encoders
};

#endif
