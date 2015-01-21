#include <UniversalInput.h>
#include <UniversalJoysticks.h>

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  joysticks.poll();
}
