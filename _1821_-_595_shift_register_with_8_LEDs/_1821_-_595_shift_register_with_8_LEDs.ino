/*  1821 - 8 LEDs controlled by one 595 shift register
 * 
 * This sketch shows you how to drive 8 outputs (connected to LEDs) using a three digital
 * pins on the Arduino. This is done with the help of a 595 shift register.
 * 
 * The sketch causes the LEDs to light up randomly.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 8 x 330 Ohm resistor for the LEDs
 *  - 1 x 74HC595 shift register
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
*  Arduino Uno and 74HC959:
 *  
 *  Arduino Uno   |     74HC959
 *  ------------------------------
 *        5V      |       16
 *        GND     |       8
 *        8       |       14 
 *        9       |       12
 *        10      |       11
 *        
 *        
 *  74HC959 and LEDs:
 *  
 *  Connect 595 pins 1 to 7 and 15 to the LEDS via their current limiting resistors.
 *     
 *  
 *  
 *  Created on May 13 2017 by Peter Dalmaris
 * 
 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  randomSeed(analogRead(0));

}

void loop() {
  byte randNumber1 = random(255);
  writeLeds(randNumber1);
  delay(100);  
}

void writeLeds(byte pattern)
{
  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
  }


