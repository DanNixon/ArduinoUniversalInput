/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H
#define _ARDUINOUNIVERSALINPUTS_IINPUTDEVICE_H

#include "UniversalInputTypes.h"

/*!
 * \class IInputDevice
 * \brief Represents an input device.
 *
 * Provides basic functionality for an abstract input device.
 */
class IInputDevice
{
public:
  /*!
   * \brief Creates a new input device.
   * \param id ID of the inout device
   */
  IInputDevice(inputid_t id)
      : m_id(id)
  {
  }

  virtual ~IInputDevice()
  {
  }

  /*!
   * \brief Retrieves the ID of this device.
   * \return Device ID
   */
  inputid_t getID() { return m_id; }

  /*!
   * \brief Retrieves the type of this device.
   * \return Device type
   */
  virtual inputtype_t type() = 0;

  /*!
   * \brief Polls this input device for change.
   */
  virtual bool poll() = 0;

private:
  inputid_t m_id; //!< ID of this device
};

#endif
