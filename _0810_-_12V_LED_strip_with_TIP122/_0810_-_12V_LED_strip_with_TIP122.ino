/*  0810 - 12V LED strip with TIP122 blinking
 * 
 * This sketch shows you how to drive a 12V LED strip using a TIP122 Darlington transistor.
 * 
 * The sketch makes the strip LEDs to blink on and off using an Arduino Uno digital pin.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 1 x TIP122 transistor
 *  - 1 x 1KOhm current limiting resistor for the transistor
 *  - 1 x white LED strip (various lengths are ok)
 *  - A breadboard
 *  - Jumper wires
 *  - A wall socket 12V power supply, 12V battery, or bench power supply for powering the LED strip
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *  
 *  See the schematic that is provided with this lecture.
 *        
 *  Other information
 *  ------------------
 *  For more info on the TIP122, see https://www.onsemi.com/pub/Collateral/TIP120-D.PDF
 *  
 *  Created on May 23 2017 by Peter Dalmaris
 * 
 */

int led_pin = 9;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
