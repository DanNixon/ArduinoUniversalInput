ArduinoUniversalButtons
=======================

Lately I have seen myself write almost identical code for managing button presses in three different Arduino projects, I was fed up with the code duplication so wrote this.

Functionality
-------------

This library is very similar to the [Button](http://playground.arduino.cc/Code/Button) library on a per abstract button basis, however this library also offers the following:

*  The ability to configure switch multiple matrices and simple pull high/low buttons withing the same handler wrapper
*  The ability to set the pin configuration (pullup, active low) per button
*  The ability to define custom IO functions for both simple buttons and matrices, allowing the library to work with whatever custom hardware is driving your switches
*  The choice of callbacks which trigger whenever a button state change is detected or when a button has been pressed and released (which also provides the amount of time the button was held down)

Issues
------

Because of the way I store switch configurations, matrix polling is quite non optimal, the largest matrix I have used was 3x26 which had an average poll time of around 670us. I may change the way matrix polling works in the future if this proves to be an issue.
