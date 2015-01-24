#include <UniversalInput.h>
#include <UniversalJoysticks.h>

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(9600);

  // Set the callback
  joysticks.setValueChangeCallback(&joystickChanged);

  // Set a default configuration
  joysticks.setDefaultConfig(new JoystickConfig(-100, 100, 385, 520, 645, 5, 5, 5, POLARITY_POSITIVE, true, 5));

  // Add some joysticks, with custom configurations
  joysticks.addJoystick(0);
  joysticks.addJoystick(1, new JoystickConfig(   0, 100, 382, 382, 647, 0, 3, 3, POLARITY_POSITIVE, false, 5));
  joysticks.addJoystick(2);
  joysticks.addJoystick(3);
  
  // Change some configs
  joysticks.getConfig(2)->setPolarity(POLARITY_NEGATIVE);
  joysticks.getConfig(3)->setPolarity(POLARITY_NEGATIVE);
}

void loop()
{
  // Poll joysticks regularly
  joysticks.poll();
  
  delay(10);
}

// Handle joysticks being moved
void joystickChanged(joystickid_t id, joystickvalue_t value, joystickvalue_t delta)
{
  Serial.print("Joystick ID ");
  Serial.print(id);
  Serial.print(", value ");
  Serial.print(value);
  Serial.print(", delta ");
  Serial.println(delta);
}
