#include <ArduinoButton.h>

ArduinoButton button(0, 9);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(button.poll())
  {
    if(button.isActive())
    {
      Serial.println("Button has been pressed...");
    }
    else
    {
      Serial.print("Button has been released after ");
      Serial.print(button.lastActiveDuration());
      Serial.println("ms.");
    }
  }
}
