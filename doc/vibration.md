# Vibration firmware

This sample code is a reproduction of the Sens'it Discovery's Vibration mode.

## User Manual

With the Vibration firmware, your Sens'it will send a Sigfox message using the Sens'it Discovery payload format every time a movement is detected.  
You can also force a message sending with a double press on the button.

This firmware is compatible with the [sensit.io](https://www.sensit.io) application.

## How to Build

To build this firmware, use the `make vibration` command.

If you want to change the motion detection sensitivity, you can edit the `VIBRATION_THRESHOLD` and `VIBRATION_COUNT` defines.

## Sources

- [main_VIBRATION.c](../sdk/src/main_VIBRATION.c)
- [fxos8700.c](../sdk/src/sensors/fxos8700.c)
- [discovery.h](../sdk/resources/discovery.h)

## Authors

- Sens'it Team

## Copyright

- Copyright (c) 2018 Sigfox, All Rights Reserved.
