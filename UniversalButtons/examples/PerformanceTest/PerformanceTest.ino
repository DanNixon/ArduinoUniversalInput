/*
 * Performance Test
 * Basic example showing time taken to poll buttons
 * The current code sits at around 230us on an Arduino UNo running at 16MHz
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
   * Setup some basic buttons using the boards IO
   */
  buttons.addButton(9, 2);
  buttons.addButton(10, 3);
  buttons.addButton(11, 4);
  buttons.addButton(12, 11);

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
   * Set the state change callback function to handle all button presses
   * and releases
   */
  buttons.setStateChangeCallback(&button_handler);
}

void loop()
{
  uint32_t start = micros();

  buttons.poll();

  uint32_t end = micros();

  Serial.print("Completed poll in: ");
  Serial.print(end - start);
  Serial.println("us");
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
