#ifndef ARDUINO_UNIVERSAL_JOYSTICKs_CONFIG_HELPER_H
#define ARDUINO_UNIVERSAL_JOYSTICKS_CONFIG_HELPER_H

#include "UniversalInput.h"
#include "JoystickConfig.h"


/**
 * Helper class to do semi-automatic calibration of joystcks.
 */
class JoystickCalibrationHelper
{
  public:
    JoystickCalibrationHelper(JoystickConfig *config, UniversalInput::pin_t adcPin);

    /**
     * Represents types of measurments that can be taken.
     */
    enum MeasurementType
    {
      MEASUREMENT_LOW,
      MEASUREMENT_CENTRE,
      MEASUREMENT_HIGH
    };

    void setNumSamples(uint32_t numSamples);
    void setDelayTime(uint16_t delayTime);

    void sample(MeasurementType type, uint32_t numSamples = 0, uint16_t delayTime = 0);

  private:
    // The config to update
    JoystickConfig *m_config;
    // The ADC pin to sample
    UniversalInput::pin_t m_adcPin;
    // Default number of samples to take
    uint32_t m_numSamples;
    // Default delay time between samples
    uint16_t m_delayTime;

};

#endif
