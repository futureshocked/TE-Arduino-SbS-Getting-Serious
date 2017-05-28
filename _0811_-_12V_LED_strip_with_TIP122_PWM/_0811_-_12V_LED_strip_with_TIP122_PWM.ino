/*  0811 - 12V LED strip with TIP122 PWM
 * 
 * This sketch shows you how to drive a 12V LED strip using a TIP122 Darlington transistor.
 * 
 * The sketch makes the strip LEDs to fade on and off using Pulse Width Modulation. 
 * Use any PWM-capable pin on your Arduino.
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
 *  For more info on the TIP122, see http://www.farnell.com/datasheets/1690291.pdf?_ga=2.252195084.467612952.1495583474-528894072.1495583474
 *  
 *  Created on May 23 2017 by Peter Dalmaris
 * 
 */
 
int ledPin = 9;    // LED connected to digital pin 9 (PWM capable)

void setup() {
  // nothing happens in setup
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 50 milliseconds to see the dimming effect
    delay(50);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 50 milliseconds to see the dimming effect
    delay(50);
  }
}


