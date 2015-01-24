#include <UniversalInput.h>
#include <UniversalJoysticks.h>

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(9600);

  // Set the callback
  joysticks.setValueChangeCallback(&joystickChanged);

  // Add some joysticks, with custom configurations
  joysticks.addJoystick(0, new JoystickConfig(-100, 100, 395, 523, 649, 3, 3, 3, POLARITY_POSITIVE, true, 5));
  joysticks.addJoystick(1, new JoystickConfig(   0, 100, 382, 382, 647, 0, 3, 3, POLARITY_POSITIVE, false, 5));
  joysticks.addJoystick(2, new JoystickConfig(-100, 100, 382, 522, 649, 3, 3, 3, POLARITY_NEGATIVE, true, 5));
  joysticks.addJoystick(3, new JoystickConfig(-100, 100, 385, 513, 640, 3, 3, 3, POLARITY_NEGATIVE, true, 5));
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
