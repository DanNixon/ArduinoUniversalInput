/*
 * Basic example of UniversalButtons usage
 *
 * ArduinoUniversalButtons
 * Dan Nixon, dan-nixon.com
 * 23/06/2014
 */

#include "UniversalButtons.h"

UniversalButtons buttons;

/*
 * enum for button IDs
 * Not actually needed but improves code readability
 */
enum Buttons
{
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT,
  BUTTON_RIGHT
};

void setup()
{
  Serial.begin(9600);

  /*
   * Setup some basic buttons using the boards IO
   */
  buttons.addButton(BUTTON_UP, 4);
  buttons.addButton(BUTTON_DOWN, 5);
  buttons.addButton(BUTTON_LEFT, 6);
  buttons.addButton(BUTTON_RIGHT, 7);

  /*
   * Remove a button
   */
  buttons.removeButton(BUTTON_DOWN);

  /*
   * Set the state change callback function to handle all button presses
   * and releases
   */
  buttons.setStateChangeCallback(&button_handler);

  /*
   * Set the state cycle callback to report time a button has been held
   */
  buttons.setStateCycleCallback(&state_cycle_handler);
}

void loop()
{
  /*
   * Poll buttons regularly
   */
  buttons.poll();

  /*
   * Show the time BUTTON_UP has been held whilst it is being held
   */
  if(buttons.getButtonState(BUTTON_UP))
  {
    Serial.print("BUTTON_UP held for ");
    Serial.print(buttons.getTimeSinceLastChange(BUTTON_UP));
    Serial.println("ms");
  }
}

/*
 * Basic handler to print which buttons are pressed and released to serial
 */
void button_handler(buttonid_t id, uint8_t state)
{
  Serial.print("Button ");
  Serial.print(id);
  if(state)
    Serial.println(" pressed");
  else
    Serial.println(" released");
}

/*
 * Basic handler to print the amount of time a button has been held
 */
void state_cycle_handler(buttonid_t id, uint32_t time)
{
  Serial.print("Button ");
  Serial.print(id);
  Serial.print(" held for ");
  Serial.print(time);
  Serial.println("ms");
}
