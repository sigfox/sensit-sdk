# Temperature firmware

This sample code is a reproduction of the Sens'it Discovery's Temperature mode.

## User Manual

With the Temperature firmware, your Sens'it will make a temperature & relative humidity measurement every hour, and send the values in a Sigfox message using the Sens'it Discovery payload format.  
You can also force a new measurement and message sending with a double press on the button.

This firmware is compatible with the [sensit.io](https://www.sensit.io) application.

## How to Build

To build this firmware, use the `make temperature` command.

If you want to change the measurement and message sending period, you can edit the `MEASUREMENT_PERIOD` define.

## Sources

- [main_TEMPERATURE.c](../sdk/src/main_TEMPERATURE.c)
- [hts221.c](../sdk/src/sensors/hts221.c)
- [discovery.h](../sdk/resources/discovery.h)

## Authors

- Sens'it Team

## Copyright

- Copyright (c) 2018 Sigfox, All Rights Reserved.
