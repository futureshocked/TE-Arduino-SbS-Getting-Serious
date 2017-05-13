
/*  0753 - Dual seven segment display directly by the Arduino, using the SevSeg library
 * 
 * This sketch shows you how to drive a dual common cathode seven segment 
 * display using only the Arduino's digital pins. This sketch uses the SevSeg library to
 * simplify programming.
 * 
 * The sketch displays numbers from 0 to 9 on both displays.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Dual common cathode seven segment display or 2 x single seven segment displays
 *  - 2 x 330 Ohm resistor for the common cathodes
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SevSeg   (will need to install it to your Arduino IDE via the library manager)
 *
 * Connections
 * -----------
 *  Arduino Uno and seven segment display:
 *  
 *  Arduino Uno   |   Seven Seg
 *  ------------------------------
 *        10      |  Common cathode for display 1
 *        11      |  Common cathode for display 2
 *        2       |       A
 *        3       |       B
 *        4       |       C 
 *        5       |       D
 *        6       |       E
 *        7       |       F 
 *        8       |       G    
 *        9       |       Dp
 *     
 *  
 *  
 *  Created on May 13 2017 by Peter Dalmaris
 * 
 */
 
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

unsigned long timer;

void setup() {
  byte numDigits = 2;   
  byte digitPins[] = {10,11};
  byte segmentPins[] = {2,3,4,5,6,7,8,9};
  bool resistorsOnSegments = false;     // Use 'true' if on digit pins
  byte hardwareConfig = COMMON_CATHODE; 
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(1000);
}

void loop() {
  timer++;
  sevseg.setNumber(timer/1000, 1);     //This will write the value to the display. To show the new value, 
                                       //the refreshDisplay function must be called.

  if (timer == 100000)
  timer = 0;
  
  sevseg.refreshDisplay(); // Must run repeatedly
}

