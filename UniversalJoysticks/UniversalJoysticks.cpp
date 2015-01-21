#include "UniversalJoysticks.h"


using namespace UniversalInput;


UniversalJoysticks::UniversalJoysticks() :
  m_defaultConfig(new JoystickConfig()),
  m_readADC(NULL),
  m_joystickCount(0),
  m_joystickList(NULL)
{
}


UniversalJoysticks::~UniversalJoysticks()
{
  delete m_defaultConfig;
}


void UniversalJoysticks::poll()
{
  //TODO`
}


void UniversalJoysticks::setValueChangeCallback(void (* callback)(joystickid_t jid, joystickvalue_t value, joystickvalue_t delta))
{
  m_valueChangeCallback = callback;
}


JoystickConfig *UniversalJoysticks::getDefaultConfig()
{
  return m_defaultConfig;
}

void UniversalJoysticks::setDefaultConfig(JoystickConfig *config)
{
  delete m_defaultConfig;
  m_defaultConfig = config;
}


JoystickConfig *UniversalJoysticks::getConfig(joystickid_t jid)
{
  //TODO
  return NULL;
}


void UniversalJoysticks::setCustomIO(int32_t (* readADC)(pin_t pin))
{
  //TODO
}


Result UniversalJoysticks::addJoystick(pin_t pin)
{
  //TODO
  return RESULT_OK;
}


Result UniversalJoysticks::addJoystick(joystickid_t jid, pin_t pin)
{
  //TODO
  return RESULT_OK;
}


Result UniversalJoysticks::addCustomJoystick(pin_t pin)
{
  //TODO
  return RESULT_OK;
}


Result UniversalJoysticks::addCustomJoystick(joystickid_t jid, pin_t pin)
{
  //TODO
  return RESULT_OK;
}


joystickvalue_t UniversalJoysticks::getJoystickValue(joystickid_t jid)
{
  //TODO
  return 0;
}


uint16_t UniversalJoysticks::joystickCount()
{
  return m_joystickCount;
}
