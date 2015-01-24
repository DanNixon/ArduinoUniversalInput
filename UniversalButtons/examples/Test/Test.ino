/**
 * This is a test for validation, is is designed to be run as a unit test.
 */

#include "UniversalInput.h"
#include "UniversalButtons.h"

using namespace UniversalInput;

UniversalButtons buttons;


void setup()
{
  Serial.begin(9600);

  test_assert(buttons.addButton(0, 1), RESULT_OK, "Adding regular button");
  test_assert(buttons.buttonCount(), 1, "Test button count");
  test_assert(buttons.addButton(0, 2), RESULT_DEVICE_ALREADY_EXISTS, "Adding button with duplicate ID");
  test_assert(buttons.addButton(1, 1), RESULT_IO_PIN_ALREADY_IN_USE, "Adding button with duplicate IO pin");
  test_assert(buttons.addButton(1, 2), RESULT_OK, "Adding another regular button");
  test_assert(buttons.buttonCount(), 2, "Test button count");
  test_assert(buttons.removeButton(0), RESULT_OK, "Removing button");
  test_assert(buttons.buttonCount(), 1, "Test button count");
  test_assert(buttons.removeButton(1), RESULT_OK, "Removing button");
  test_assert(buttons.buttonCount(), 0, "Test button count");
}

void loop()
{
}

void test_assert(int16_t result, int16_t expected, const char *testName)
{
  Serial.print(testName);
  Serial.println("...");
  bool pass = result == expected;
  const char *resultMessage = pass ? "Passed" : "FAILED!";
  Serial.println(resultMessage) ;
}
