#include "UniversalJoysticks.h"


using namespace UniversalInput;


joystickraw_t joystickAnalogRead(pin_t pin)
{
  return (joystickraw_t) analogRead(pin);
}


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
  Joystick *joystick = m_joystickList;

  while(joystick)
  {
    pin_t pin = joystick->adcPin;
    joystickraw_t rawValue = joystick->adcRead(pin);
    joystickvalue_t value = joystick->config->convertRaw(rawValue);
    joystickvalue_t delta = abs(joystick->lastValue - value);

    if(delta > joystick->config->getDeltaThreshold())
    {
      if(m_valueChangeCallback)
        m_valueChangeCallback(joystick->id, value, delta);

      joystick->lastValue = value;
    }

    joystick = joystick->next;
  }
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
  Joystick *joystick = m_joystickList;

  while(joystick)
  {
    if(joystick->id == jid)
      return joystick->config;

    joystick = joystick->next;
  }

  return NULL;
}


void UniversalJoysticks::setCustomIO(joystickraw_t (* readADC)(pin_t pin))
{
  m_readADC = readADC;
}


Result UniversalJoysticks::addJoystick(pin_t pin, JoystickConfig *config)
{
  return addJoystick(pin, pin, config);
}


Result UniversalJoysticks::addJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config)
{
  Joystick *newJoystick = new Joystick;
  newJoystick->id = jid;
  newJoystick->adcPin = pin;
  newJoystick->adcRead = &joystickAnalogRead;
  newJoystick->lastValue = 0;
  newJoystick->next = NULL;

  if(config != NULL)
    newJoystick->config = config;
  else
    newJoystick->config = new JoystickConfig();

  joystickListAppend(newJoystick);

  return RESULT_OK;
}


Result UniversalJoysticks::addCustomJoystick(pin_t pin, JoystickConfig *config)
{
  return addCustomJoystick(pin, pin, config);
}


Result UniversalJoysticks::addCustomJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config)
{
  if(!m_readADC)
    return RESULT_NO_CUSTOM_IO;

  Joystick *newJoystick = new Joystick;
  newJoystick->id = jid;
  newJoystick->adcPin = pin;
  newJoystick->adcRead = m_readADC;
  newJoystick->lastValue = 0;
  newJoystick->next = NULL;

  if(config != NULL)
    newJoystick->config = config;
  else
    newJoystick->config = new JoystickConfig();

  joystickListAppend(newJoystick);

  return RESULT_OK;
}


Result UniversalJoysticks::removeJoystick(joystickid_t jid)
{
  if(m_joystickCount == 0)
  {
    return RESULT_NO_SUCH_DEVICE;
  }
  if(m_joystickCount == 1)
  {
    if(m_joystickList->id == jid)
    {
      delete m_joystickList;
      m_joystickCount--;

      return RESULT_OK;
    }
  }
  else
  {
    Joystick *prev = NULL;
    Joystick *current = m_joystickList;

    while(current)
    {

      if(current->id == jid)
      {
        if(current->next)
        {
          if(prev)
            prev->next = current->next;
          else
            m_joystickList = current->next;
        }

        delete current;

        return RESULT_OK;
      }

      prev = current;
      current = current->next;
    }
  }

  return RESULT_NO_SUCH_DEVICE;
}


joystickvalue_t UniversalJoysticks::getJoystickValue(joystickid_t jid)
{
  Joystick *joystick = m_joystickList;

  while(joystick)
  {
    if(joystick->id == jid)
      return joystick->lastValue;

    joystick = joystick->next;
  }

  return -1;
}


uint16_t UniversalJoysticks::joystickCount()
{
  return m_joystickCount;
}


void UniversalJoysticks::joystickListAppend(Joystick *joystick)
{
  if(!m_joystickList)
  {
    m_joystickList = joystick;
  }
  else
  {
    Joystick *ptr = m_joystickList;

    while(ptr->next)
    {
      ptr = ptr->next;
    }

    ptr->next = joystick;
  }

  m_joystickCount++;
}
