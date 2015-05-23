#include <ArduinoJoystick.h>

ArduinoJoystick joystick(0, 1);

void setup()
{
  Serial.begin(9600);
  
  joystick.setPoints(380, 644);
  joystick.setDeadbands(5, 5);
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
