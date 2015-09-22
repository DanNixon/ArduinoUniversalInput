#include <UniversalInputManager.h>
#include <IUniversalInputCallback.h>
#include <ArduinoButton.h>
#include <ArduinoMatrixButton.h>

class Handler: public IUniversalInputCallback
{
public:
	Handler():
		IUniversalInputCallback()
	{
	}
	
	void handleUniversalInputEvent(inputtype_t type, IInputDevice * device)
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
};

UniversalInputManager inputs;
Handler handler;

void setup()
{
  Serial.begin(9600);

  inputs.addDevice(new ArduinoButton(0, 6));
  inputs.addDevice(new ArduinoButton(0, 7));  // This button should not be added as it has a duplicate ID
  inputs.addDevice(new ArduinoButton(2, 8));
  inputs.addDevice(new ArduinoMatrixButton(3, 9, 10));

  inputs.setCallback(&handler);
}

void loop()
{
  inputs.poll();
}
