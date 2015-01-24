#include <UniversalInput.h>
#include <UniversalJoysticks.h>
#include <JoystickCalibrationHelper.h>

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(9600);

  // Set the callback
  joysticks.setValueChangeCallback(&joystickChanged);

  // Add a joystick
  joysticks.addJoystick(0);
  
  // Set up the configuration helper
  JoystickCalibrationHelper configHelper(joysticks.getConfig(0), 0);
  configHelper.setNumSamples(1000);
  configHelper.setDelayTime(10);
  
  Serial.print("Calibrate lower...");
  delay(1000);
  Serial.println("start.");
  configHelper.sample(JoystickCalibrationHelper::MEASUREMENT_LOW);
  
  Serial.print("Calibrate centre...");
  delay(1000);
  Serial.println("start.");
  configHelper.sample(JoystickCalibrationHelper::MEASUREMENT_CENTRE);
  
  Serial.print("Calibrate upper...");
  delay(1000);
  Serial.println("start.");
  configHelper.sample(JoystickCalibrationHelper::MEASUREMENT_HIGH);
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
