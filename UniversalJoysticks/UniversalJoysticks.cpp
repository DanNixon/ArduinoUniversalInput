#include "UniversalJoysticks.h"


/**
 * Function to cast the result of an analogRead to the required
 * joystickraw_t integer type.
 *
 * @param pin ADC pin to measure
 * @return ADC value
 */
joystickraw_t joystickAnalogRead(pin_t pin)
{
  return (joystickraw_t) analogRead(pin);
}


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


/**
 * Checks all configured joysticks for changes in position.
 */
void UniversalJoysticks::poll()
{
  joystick_t *joystick = m_joystickList;

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


/**
 * Sets the callback for when a value is changed.
 *
 * @param callback Pointer to the function to call
 */
void UniversalJoysticks::setValueChangeCallback(void (* callback)(joystickid_t jid, joystickvalue_t value, joystickvalue_t delta))
{
  m_valueChangeCallback = callback;
}


/**
 * Returns the default joystick configuration.
 *
 * @return Default configuration
 */
JoystickConfig *UniversalJoysticks::getDefaultConfig()
{
  return m_defaultConfig;
}


/**
 * Sets the default configuration for new joysticks.
 *
 * @param config Pointer to configuration
 */
void UniversalJoysticks::setDefaultConfig(JoystickConfig *config)
{
  delete m_defaultConfig;
  m_defaultConfig = config;
}


/**
 * Gets the configuration for a given joystick by ID.
 *
 * @param jid Joystick ID
 * @return Joystick configuration
 */
JoystickConfig *UniversalJoysticks::getConfig(joystickid_t jid)
{
  joystick_t *joystick = m_joystickList;

  while(joystick)
  {
    if(joystick->id == jid)
      return joystick->config;

    joystick = joystick->next;
  }

  return NULL;
}


/**
 * Sets the ADC read function for joysticks added using custom IO.
 *
 * @param readADC Pointer to ADC read function
 */
void UniversalJoysticks::setCustomIO(joystickraw_t (* readADC)(pin_t pin))
{
  m_readADC = readADC;
}


/**
 * Adds a new joystick using the pin number as the ID.
 *
 * @param pin ADC pin
 * @param config Optional joystick configuration
 * @return Result of addition
 */
result_t UniversalJoysticks::addJoystick(pin_t pin, JoystickConfig *config)
{
  return addJoystick(pin, pin, config);
}


/**
 * Adds a new joystick on a given on board ADC pin.
 *
 * @param jid New joystick ID
 * @param pin ADC pin
 * @param config Optional joystick configuration
 * @return Result of addition
 */
result_t UniversalJoysticks::addJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config)
{
  joystick_t *newJoystick = new joystick_t;
  newJoystick->id = jid;
  newJoystick->adcPin = pin;
  newJoystick->adcRead = &joystickAnalogRead;
  newJoystick->lastValue = 0;
  newJoystick->next = NULL;

  if(config != NULL)
    newJoystick->config = config;
  else
    newJoystick->config = new JoystickConfig(*m_defaultConfig);

  return joystickListAppend(newJoystick);
}


/**
 * Adds a new joystick using custom IO and using the pin number as the ID.
 *
 * @param pin ADC pin
 * @param config Optional joystick configuration
 * @return Result of addition
 */
result_t UniversalJoysticks::addCustomJoystick(pin_t pin, JoystickConfig *config)
{
  return addCustomJoystick(pin, pin, config);
}


/**
 * Adds a joystick using custom IO.
 *
 * @param jid ID of new joystick
 * @param pin ADC pin
 * @param config Optional joystick configuration
 * @return Result of addition
 */
result_t UniversalJoysticks::addCustomJoystick(joystickid_t jid, pin_t pin, JoystickConfig *config)
{
  if(!m_readADC)
    return RESULT_NO_CUSTOM_IO;

  joystick_t *newJoystick = new joystick_t;
  newJoystick->id = jid;
  newJoystick->adcPin = pin;
  newJoystick->adcRead = m_readADC;
  newJoystick->lastValue = 0;
  newJoystick->next = NULL;

  if(config != NULL)
    newJoystick->config = config;
  else
    newJoystick->config = new JoystickConfig(*m_defaultConfig);

  return joystickListAppend(newJoystick);
}


/**
 * Removes a joystick given its ID.
 *
 * @param jid Jostick ID
 * @return Result of deletion
 */
result_t UniversalJoysticks::removeJoystick(joystickid_t jid)
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
    joystick_t *prev = NULL;
    joystick_t *current = m_joystickList;

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
        m_joystickCount--;

        return RESULT_OK;
      }

      prev = current;
      current = current->next;
    }
  }

  return RESULT_NO_SUCH_DEVICE;
}


/**
 * Gets the last recorded value for a joystick.
 *
 * @param jid ID of Joystick
 * @return Last recorded value
 */
joystickvalue_t UniversalJoysticks::getJoystickValue(joystickid_t jid)
{
  joystick_t *joystick = m_joystickList;

  while(joystick)
  {
    if(joystick->id == jid)
      return joystick->lastValue;

    joystick = joystick->next;
  }

  return -1;
}


/**
 * Gets the number of joysticks added.
 *
 * @return Joystick count
 */
uint16_t UniversalJoysticks::joystickCount()
{
  return m_joystickCount;
}


/**
 * Adds a new joystick to the linked list.
 * Performs checking for duplicate IDs and ADC pins already in use.
 *
 * @param joystick Joystick to append
 * @return Result of addition
 */
result_t UniversalJoysticks::joystickListAppend(joystick_t *joystick)
{
  if(!m_joystickList)
  {
    m_joystickList = joystick;
    m_joystickCount++;
    return RESULT_OK;
  }
  else
  {
    joystick_t *ptr = m_joystickList;

    while(ptr->next)
    {
      if(ptr->id == joystick->id)
        return RESULT_DEVICE_ALREADY_EXISTS;

      if(ptr->adcPin == joystick->adcPin)
        return RESULT_IO_PIN_ALREADY_IN_USE;

      ptr = ptr->next;
    }

    if(ptr->id == joystick->id)
      return RESULT_DEVICE_ALREADY_EXISTS;

    if(ptr->adcPin == joystick->adcPin)
      return RESULT_IO_PIN_ALREADY_IN_USE;

    ptr->next = joystick;
  }

  m_joystickCount++;
  return RESULT_OK;
}
