# Twinkle Tree Basic

## Description
Non-Home Assistant controlled version of Twinkle Tree.  Operates
in 5 modes: "Fade In", "Fade In/Out", "Blink", "Spooky" and "None"
mode, in which brightness can be controlled with a linear pot. 
Cycling through modes is achieved by press of a button.

## Hardware
- ATtiny85 PU.
- IRLZ44N N-channel MOSFET (logic level).
- 67 K&#937; resistor.
- 50 K&#937; linear potentiometer.
- 5V/2A (10W) Power source.
- capacitive push button.
- USBTiny compatible AVR programmer.
![Schematic](/assets/schem.png)

## Software dependencies
- Arduino libraries.
- arminjo/ATtinySerialOut@^2.3.1 (for serial debugging). 
- PlatformIO VSCode extension.