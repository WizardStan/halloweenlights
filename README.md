# Halloween Lights
================

Simple pic16 program (using a pic18f4550) to intermittently blink LEDs for "spooky" eyes.

### Hardware
 - Microchip PIC 18f4550
 - MCLR tied to VDD
 - Cardboard tubes (ie, toilet paper)
 - Red LEDs

### Building
 - make
 - make flash

### Assembly Instructions
 - Cut eye holes in the cardboard tubes
 - Solder LED to sufficiently long wires to be able to spread out your eyes a bit
 - Place LED in tube such that all light is exposed through the eye holes.  It may be best to simply cut a hole directly behind the eye sockets and push the LED in there.
 - Seal up the ends with duct tape
 - Connect LED cathode to common ground, connect anode to designated PIC pin.  A small 1k ohm resistor may be desirable but is not necessary.
 
