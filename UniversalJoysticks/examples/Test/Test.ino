/**
 * This is a test for validation, is is designed to be run as a unit test.
 */

#include <UniversalInput.h>
#include <UniversalJoysticks.h>

using namespace UniversalInput;

UniversalJoysticks joysticks;

void setup()
{
  Serial.begin(9600);

  test_assert(joysticks.addJoystick(0, 1), RESULT_OK, "Adding regular joystick");
  test_assert(joysticks.addJoystick(0, 2), RESULT_DEVICE_ALREADY_EXISTS, "Adding joystick with duplicate ID");
  test_assert(joysticks.addJoystick(1, 1), RESULT_IO_PIN_ALREADY_IN_USE, "Adding joystick with duplicate ADC pin");
  test_assert(joysticks.addJoystick(1, 2), RESULT_OK, "Adding another regular joystick");
  test_assert(joysticks.joystickCount(), 2, "Test joystick count");
  test_assert(joysticks.removeJoystick(0), RESULT_OK, "Removing joystick");
  test_assert(joysticks.joystickCount(), 1, "Test joystick count");
  test_assert(joysticks.removeJoystick(5), RESULT_NO_SUCH_DEVICE, "Removing joystick that does not exist");
  test_assert(joysticks.joystickCount(), 1, "Test joystick count");
  test_assert(joysticks.removeJoystick(1), RESULT_OK, "Removing joystick");
  test_assert(joysticks.joystickCount(), 0, "Test joystick count");
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
