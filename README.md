# swt16midi v0.1.0
Alternative midi to gate firmware for the [robaux swt16](https://robaux.io/swt16) with accompanying Max for Live device

This is a firmware for the swt16 rev1 (with the Arduino Nano on it), or rev2 with [the included adapter board](https://www.instagram.com/p/Bju6L2hgjEA/)+arduino nano.
It overrides the original functionality and now you can use it a 16 channel midi to trigger/gate device for use with Ableton (it uses a simplified midi protocol that is handled by a Max for Live midi device, that also handles all the settings).

The swt16 knobs can be used to mute the channels (a little flicker indicates muted notes). The blue led under the home button indicates midi activity (the button does nothing).

The swt16 is connected to the computer with a usb cable connected to the usb port of the arduino nano.
You need to select the right serial port in the max for live device (something like wchusb1410), keep in mind that the port name probably changes if you plug it into a different usb port.
You can choose for each port if it functions a fixed length trigger (using a user definable global length) or as gate that follows the note on/off. A button is included to stop all notes at once.

# demo
https://www.instagram.com/p/B0lTnlDBWB8/ 

https://www.instagram.com/p/B0lJ3TkBhDt/

#
original firmware used as a base to make this: https://github.com/robaux/swt16/
