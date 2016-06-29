#include <Adafruit_MCP23017.h>
#include <UniversalInputManager.h>
#include <MCP23017Button.h>

#define INTERRUPT_PIN 2
#define INTERRUPT_NUM 0

Adafruit_MCP23017 mcp;
UniversalInputManager inputs;

volatile bool need_to_poll;

void setup()
{
  Serial.begin(9600);

  /* MCP23017 setup */
  mcp.begin();
  mcp.setupInterrupts(true, false, LOW);

  /* Interrupt setup */
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  need_to_poll = true;

  /* Add all pins */
  for (uint8_t i = 0; i < 15; i++)
    inputs.addDevice(new MCP23017Button(&mcp, i, i));

  inputs.setCallback(handler);
}

void loop()
{
  attachInterrupt(INTERRUPT_NUM, handle_interrupt, FALLING);

  while (!need_to_poll)
  {
  }

  detachInterrupt(INTERRUPT_NUM);

  if (need_to_poll)
  {
    inputs.poll();
    need_to_poll = false;
  }
}

void handle_interrupt()
{
  need_to_poll = true;
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
