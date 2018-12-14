# Magnet firmware

This sample code is a reproduction of Sens'it Discovery's Magnet mode.

## User Manual

With the Magnet firmware, your Sens'it can send a Sigfox message using the Sens'it Discovery payload format every time a magnet is detected or removed from the device.  
You can also force a message sending with a double press on the button.

This firmware is compatible with the [sensit.io](https://www.sensit.io) application.

## How to Build

To build this firmware, use the `make magnet` command.

## Sources

- [main_MAGNET.c](../sdk/src/main_MAGNET.c)
- [discovery.h](../sdk/resources/discovery.h)

## Authors

- Sens'it Team

## Copyright

- Copyright (c) 2018 Sigfox, All Rights Reserved.
