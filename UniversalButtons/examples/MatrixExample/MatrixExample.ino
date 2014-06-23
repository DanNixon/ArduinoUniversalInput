/*
 * Switch matrix example
 *
 * ArduinoUniversalButtons
 * Dan Nixon, dan-nixon.com
 * 23/06/2014
 */

#include "UniversalButtons.h"

UniversalButtons buttons;

void setup()
{
  Serial.begin(9600);

  /*
   * Setup switch matrix using board IOs
   * (ID, row pin, column pin)
   */
  buttons.addButton(0, 5, 8);
  buttons.addButton(1, 5, 9);
  buttons.addButton(2, 5, 10);
  buttons.addButton(3, 6, 8);
  buttons.addButton(4, 6, 9);
  buttons.addButton(5, 6, 10);
  buttons.addButton(6, 7, 8);
  buttons.addButton(7, 7, 9);
  buttons.addButton(8, 7, 10);

  /*
   * Set the callback function to handle all button presses and releases
   */
  buttons.setCallback(&button_handler);
}

void loop()
{
  /*
   * Poll buttons regularly
   */
  buttons.poll();
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
