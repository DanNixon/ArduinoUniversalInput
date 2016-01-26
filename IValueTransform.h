/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H
#define _ARDUINOUNIVERSALINPUTS_IVALUETRANSFORM_H

#include "UniversalInputTypes.h"

/*!
 * \class IValueTransform
 * \brief Interface for a value transformation.
 */
class IValueTransform
{
public:
  /*!
   * \brief Create a new value transformation.
   * \param fromLow Lowest mapped inout value
   * \param fromHigh Highest mapped input value
   */
  IValueTransform(inputanalog_t fromLow, inputanalog_t fromHigh)
      : m_fromLow(fromLow)
      , m_fromHigh(fromHigh)
  {
  }

  virtual ~IValueTransform()
  {
  };

  /*!
   * \brief Perform the value transformation.
   * \param raw Value to transform
   * \return Transformed value
   */
  virtual inputanalog_t transform(inputanalog_t raw) const = 0;

protected:
  inputanalog_t m_fromLow; //!< Lowest input value
  inputanalog_t m_fromHigh; //!< Highest input value
};

#endif
