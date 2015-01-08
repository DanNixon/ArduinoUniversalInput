#ifndef ARDUINO_UNIVERSAL_JOYSTICKS_H
#define ARDUINO_UNIVERSAL_JOYSTICKS_H

#include <Arduino.h>
#include <inttypes.h>

#define DEFAULT_DELTA_THRESHOLD 10

typedef uint16_t joystickid_t;
typedef int32_t joystickvalue_t;
typedef uint8_t pin_t;

struct JoystickConfig
{
  joystickvalue_t toRangeHigh;
  joystickvalue_t toRangeLow;

  int32_t fromRangeHigh;
  int32_t fromRangeLow;

  int32_t centrePoint;

  int32_t deadBandWidthHigh;
  int32_t deadBandWidthCentre;
  int32_t deadBandWidthLow;

  joystickvalue_t deltaThreshold;
};

struct Joystick
{
  buttonid_t id;
  JoystickConfig *config;
  joystickvalue_t (* adcRead) (pin_t pin);
  joystickvalue_t lastValue;
  Joystick *next;
};

class UniversalJoysticks
{
  public:
    UniversalJoysticks();
    ~UniversalJoysticks();

    void poll();

    void setValueChangeCallback(void (* callback)(joystickid_t jid, joystickvalue_t value));

    JoystickConfig *getDefaultConfig();
    JoystickConfig *getConfig(joystickid_t jid);

    void setCustomIO(int32_t (* readADC)(pin_t pin));

    void addJoystick(pin_t pin);
    void addJoystick(joystickid_t jid, pin_t pin);

    joystickvalue_t getJoystickValue(joystickid_t jid);

    uint16_t joystickCount();

  private:
    JoystickConfig defaultConfig;

    int32_t (* _readADC)(pin_t pin);

    uint16_t _joystickCount;
    Joystick *_joystickList;
};

#endif
