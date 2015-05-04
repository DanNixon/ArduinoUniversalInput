#include "JoystickCalibrationHelper.h"

#include <Arduino.h>
#include "JoystickTypes.h"

using UniversalInput::pin_t;


JoystickCalibrationHelper::JoystickCalibrationHelper(JoystickConfig *config, pin_t adcPin) :
  m_config(config), m_adcPin(adcPin), m_numSamples(100), m_delayTime(10)
{
}


/**
 * Sets the default number of samples to take.
 *
 * @param numSamples Number of samples
 */
void JoystickCalibrationHelper::setNumSamples(uint32_t numSamples)
{
  m_numSamples = numSamples;
}


/**
 * Set the default time delay between samples.
 *
 * @param delayTime Time delay in milliseconds
 */
void JoystickCalibrationHelper::setDelayTime(uint16_t delayTime)
{
  m_delayTime = delayTime;
}


/**
 * Take samples and apply calibration to config.
 *
 * @param type Measurement type to take
 * @param numSamples Number of samples
 * @param delayTime Time delay between samples in milliseconds
 */
void JoystickCalibrationHelper::sample(measurementtype_t type, uint32_t numSamples, uint16_t delayTime)
{
  if(numSamples == 0)
    numSamples = m_numSamples;

  if(delayTime == 0)
    delayTime = m_delayTime;

  joystickraw_t acc = 0;
  joystickraw_t min = INT32_MAX;
  joystickraw_t max = INT32_MIN;

  // Take samples
  for(uint32_t i = 0; i < numSamples; i++)
  {
    joystickraw_t value = (joystickraw_t) analogRead(m_adcPin);

    if(value < min)
      min = value;

    if(value > max)
      max = value;

    acc += value;

    delay(delayTime);
  }

  acc /= numSamples;
  joystickraw_t deadBandWidth = max - min;

  // Update the config
  switch(type)
  {
    case MEASUREMENT_LOW:
      m_config->setFromLow(acc);
      m_config->setDeadBandLow(deadBandWidth);
      break;
    case MEASUREMENT_CENTRE:
      m_config->setFromCentre(acc);
      m_config->setDeadBandCentre(deadBandWidth);
      break;
    case MEASUREMENT_HIGH:
      m_config->setFromHigh(acc);
      m_config->setDeadBandHigh(deadBandWidth);
      break;
  }
}
