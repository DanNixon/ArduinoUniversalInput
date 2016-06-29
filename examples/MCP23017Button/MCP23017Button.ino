#include <Adafruit_MCP23017.h>
#include <UniversalInputManager.h>
#include <MCP23017Button.h>

Adafruit_MCP23017 mcp;
UniversalInputManager inputs;

void setup()
{
  Serial.begin(9600);

  /* MCP23017 setup */
  mcp.begin();

  /* Add all pins */
  for (uint8_t i = 0; i < 15; i++)
    inputs.addDevice(new MCP23017Button(&mcp, i, i));

  inputs.setCallback(handler);
}

void loop()
{
  inputs.poll();
}

void handler(inputtype_t type, IInputDevice * device)
{
  if(type == UIT_BUTTON)
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
  }
}
