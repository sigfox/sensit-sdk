# Modem firmware

This firmware turns your device into an AT commands modem and allows to send Sigfox messages through USB or UART commands.

## How to Build

To build this firmware, use the `make modem` command.

Build with the `-DUSB` flag to use USB communication.  
Build with the `-DUART` flag to use UART communication.  
To know how to connect to the UART of your Sens'it see `sensit-backside-pinout.png`.

If you want to use an external power supply, build with the `-DEXTERNAL_POWER` flag to disable the battery charger, so that you will not damage your power supply.

If you want the Sigfox test modes AT command (AT$TM), build with `-DUART -DTEST_MODE`.  
Be aware that the device will use the test mode credentials and will not be able to communicate on the Sigfox Network.

## Serial Link Settings

- Data Rate: 115.200 bps.
- Parity: None.
- Bit: 8.
- Stop bit: 1.
- CR line end

## AT Commands List

### ATZ
- **Brief:** Software reset.

### AT$ID?
- **Brief:** Print the device ID.

### AT$V?
- **Brief:** Print the Sens'it SDK version.

### AT$V=[type]
- **Brief:** Print the Sigfox library version, or Manufacturer APIs version.
- **[type]:** Version type.
    - 0: Sigfox APIs version.
    - 1: MCU APIs version.
    - 2: RF APIs version.

### AT$RC?
- **Brief:** Print the currently used Radio Configuration.

### AT$RC=[rc]
- **Brief:** Set the Radio Configuration. Must be called before `AT$SF` or `AT$TM`.
- **[rc]:** Radio Configuration.
    - 0: RC1.
    - 1: RC2.
    - 2: RC3c.
    - 3: RC4.

### ATS410?
- **Brief:** Print the type of AES key currently used (PRIVATE or PUBLIC).

### ATS410=[type]
- **Brief:** Set the type of AES key to use. Only for AT$SF command.
- **[type]:** Key type.
    - 0: Private key.
    - 1: Public key (0x00112233445566778899AABBCCDDEEFF).

### AT$SF=[data]
- **Brief:** Send a Sigfox messages.
- **[data]:** Data to send, in hexadecimal format, maximum 12 bytes.

### AT$CW=[frequency],[type]
- **Brief:** Start a continuous wave emission. Press the button to stop it.
- **[frequency]:** Carrier center frequency.
- **[type]:** Modulation type.
    - 0: No modulation.
    - 1: D-BPSK 100 bps.
    - 2: D-BPSK 600 bps.

### AT$TM?
- **Brief:** Print the test mode library version.

### AT$TM=[mode]
- **Brief:** Activate a Sigfox test mode.
- **[mode]:** Mode to activate.
    - 0: Tx BPSK.
    - 1: Tx Protocol.
    - 2: Rx Protocol.
    - 3: Rx GFSK.
    - 4: Rx Sensitivity.
    - 5: Tx Frequency Synthesis.
    - 6: Tx Frequency Distribution.


## Sources

- [main_MODEM.c](../sdk/src/main_MODEM.c)
- [AT_parser.c](../sdk/src/ressource/AT_parser.c)
- [AT_functions.c](../sdk/src/resources/AT_functions.c)

## Authors

- Sens'it Team

## Copyright

- Copyright (c) 2018 Sigfox, All Rights Reserved.
