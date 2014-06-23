ArduinoUniversalButtons
=======================

Lately I have seen myself write almost identical code for managing button presses in three different Arduino projects, I was fed up with the code duplication so wrote this.

Functionality
-------------

On a per button basis the library is very similar to the [Button](http://playground.arduino.cc/Code/Button) library, in that it allows easy access to past states and event driven input handling.

The main three differences are that it allows the configuration of both matrix wired and basic pull high/pull low switches on the same set of handlers and allows configuration of unlimited buttons per object.   
Why is that important? I believe it helps to keep code tidier.

And the ability for the user to define their own function for checking the state of a button (or setting/reading matrix columns/rows), this makes the library compatible with any large matrix configurations which use dedicated hardware (e.g. shift registers).
