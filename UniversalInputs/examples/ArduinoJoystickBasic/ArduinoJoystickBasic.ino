#include <ArduinoJoystick.h>

ArduinoJoystick joystick(0, 0);

void setup()
{
  Serial.begin(9600);
  
  joystick.setPoints(393, 521, 647);
  joystick.setDeadbands(5, 5, 5);
  joystick.setThreshold(5);
}

void loop()
{
  if(joystick.poll())
  {
    Serial.print("Joystick has been moved to ");
    Serial.print(joystick.getValue());
    Serial.print(" (raw=");
    Serial.print(joystick.getRawValue());
    Serial.println(")");
  }
}
