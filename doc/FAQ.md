# F.A.Q.

## I do not receive messages sent by my Sens'it. Why?

1. You may not be using the right Radio Configuration for your current location.  
You can check on [Sigfox Build](https://build.sigfox.com/sigfox-radio-configurations-rc#geographical-availability) which Sigfox Radio Configuration you should use.

2. The sequence number of your device may have been reset, or too many messages may have been sent without being received. You need to **disengage the sequence number** of your device.   

3. Check the error code of functions `RADIO_API_send_message` and/or `SIGFOX_API_send_frame` to see if messages are really sent.

4. Be sure you have [Sigfox coverage](https://www.sigfox.com/en/coverage) at your location.

## How do I disengage the sequence number of my device ?

To do this you need to have access to your device on [backend.sigfox.com](https://backend.sigfox.com/).  
Go to your device's `Information` page, and click on the button `Disengage sequence number` located at the top right of the page.

## What should I do if my Sens'it stays in bootloader mode after a re-flash?

If your Sens'it does not restart at the end of the re-flash, you must remove the battery and the USB cable to force the restart, or wait for the battery to discharge.

## I have not implemented a way to reset the device in my code. How can I put my Sens'it in bootloader mode again?

You must remove the battery and the USB cable, then press the button and connect the USB cable. Your device will start up in bootloader.

## Why does the main LED of my Sens'it blink alternatively red and white?

A HardFault has occurred.  
It is certainly a segmentation fault. Check pointers and size of arrays in your code.
