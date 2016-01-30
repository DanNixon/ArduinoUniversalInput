/*! \file */

#ifndef _ARDUINOUNIVERSALINPUTS_LINEARVALUETRANSFORM_H
#define _ARDUINOUNIVERSALINPUTS_LINEARVALUETRANSFORM_H

#include "IValueTransform.h"

/*!
 * \class LinearTransform
 * \brief Value transformation for basic linear interpolation.
 */
class LinearTransform : public IValueTransform
{
public:
  /*!
   * \copydoc IValueTransform::IValueTransform
   * \param toLow Lowest mapped output value
   * \param toHigh Highest mapped output value
   */
  LinearTransform(inputanalog_t fromLow, inputanalog_t fromHigh,
                  inputanalog_t toLow, inputanalog_t toHigh)
      : IValueTransform(fromLow, fromHigh)
      , m_toLow(toLow)
      , m_toHigh(toHigh)
  {
  }

  virtual ~LinearTransform()
  {
  }

  /*!
   * \copydoc IValueTransform::transform
   *
   * Performs basic linear interpolation.
   */
  inputanalog_t transform(inputanalog_t raw) const
  {
    if (raw == 0)
      return 0;

    return (raw - m_fromLow) * (m_toHigh - m_toLow) / (m_fromHigh - m_fromLow) +
           m_toLow;
  }

private:
  inputanalog_t m_toLow; //!< Lowest output value
  inputanalog_t m_toHigh; //!< Highest output value
};

#endif
