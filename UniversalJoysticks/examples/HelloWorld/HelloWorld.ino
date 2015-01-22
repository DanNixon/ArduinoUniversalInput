#include <UniversalInput.h>
#include <UniversalJoysticks.h>

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(9600);

  // Set the callback
  joysticks.setValueChangeCallback(&joystickChanged);

  // Add some joysticks
  joysticks.addJoystick(0);
  joysticks.addJoystick(1);
  joysticks.addJoystick(2);
  joysticks.addJoystick(3);
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
