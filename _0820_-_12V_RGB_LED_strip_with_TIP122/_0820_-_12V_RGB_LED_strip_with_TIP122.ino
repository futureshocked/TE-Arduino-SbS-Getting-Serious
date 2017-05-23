/*  0820 - 12V RGB LED strip with TIP122 PWM
 * 
 * This sketch shows you how to drive a 12V RGB LED strip using a TIP122 Darlington transistor.
 * 
 * The sketch makes the strip RGB LEDs to show random colors.
 * This is done by producing random PWM values to each of the three PWM-capable
 * pins that drive the RGB LED strip.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 3 x TIP122 transistor
 *  - 3 x 1KOhm current limiting resistor for the transistor
 *  - 1 x RGB LED strip (various lengths are ok)
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
 
int ledPin1 = 9;    // LED connected to digital pin 9 (PWM capable)
int ledPin2 = 10;    // LED connected to digital pin 9 (PWM capable)
int ledPin3 = 11;    // LED connected to digital pin 9 (PWM capable)

void setup() {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {

  analogWrite(ledPin1,random(255)); //Write a random PWM value to the first color of the RGB LED strip
  analogWrite(ledPin2,random(255)); //Write a random PWM value to the second color of the RGB LED strip
  analogWrite(ledPin3,random(255)); //Write a random PWM value to the third color of the RGB LED strip
  delay(100); // Give it a short delay so that we can see this color
 
}


