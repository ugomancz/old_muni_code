Overview
========
The LCD demo application provides a simple demonstration of the LCD driver usage.

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K66F board
- Personal Computer
- LCD 1602A display with a cable

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Connect the LCD 1602A to target board by using the following pins:

Target board:  		LCD 1602A: 
J3_12 - GND			1 - VSS
J3_10 - P5V_USB		2 - VCC
					3 - VEE (connect a trimmer output for contrast adjustment)
J1_14 – PTC2		4 - RS
J1_12 – PTC5		5 - R/W
J1_10 – PTC12		6 - E
J1_8 – PTC8			11 - DB4
J1_6 – PTC16		12 - DB5
J1_4 – PTC4			13 - DB6
J1_2 – PTC3			14- DB7

3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
The LCD displays is initialized and a demo date/time information is displayed.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
date: DD.MM.YYYY
time: HH.MM.SS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Toolchain supported
===================
- MCUXpresso

