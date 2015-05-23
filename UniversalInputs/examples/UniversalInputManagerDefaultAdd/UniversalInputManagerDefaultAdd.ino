#include <UniversalInputManager.h>
#include <ArduinoButton.h>
#include <ArduinoJoystick.h>

UniversalInputManager inputs;

void setup()
{
  Serial.begin(9600);
  
  inputs.addNewButton(44);
  inputs.addNewButton(48);
  inputs.addNewButton(10, 42);
  inputs.addNewButton(11, 46);
  
  inputs.addNewJoystick(0);
  inputs.addNewJoystick(1);
  inputs.addNewJoystick(20, 2);
  inputs.addNewJoystick(21, 3);
  
  inputs.setCallback(handler);
}

void loop()
{
  inputs.poll();
}

void handler(UniversalInputType type, IInputDevice * device)
{
  switch(type)
  {
    case UIT_BUTTON:
    {
      IButton * button = (IButton *) device;

      if(button->isActive())
      {
        Serial.print("Button ");
        Serial.print(button->getID());
        Serial.println(" has been pressed...");
      }
      else
      {
        Serial.print("Button ");
        Serial.print(button->getID());
        Serial.print(" has been released after ");
        Serial.print(button->lastActiveDuration());
        Serial.println("ms.");
      }
      
      break;
    }
      
    case UIT_JOYSTICK:
    {
      IJoystick * joystick = (IJoystick *) device;
    
      Serial.print("Joystick ");
      Serial.print(joystick->getID());
      Serial.print(" is now at ");
      Serial.println(joystick->getValue());
      
      break;
    }
  }
}
