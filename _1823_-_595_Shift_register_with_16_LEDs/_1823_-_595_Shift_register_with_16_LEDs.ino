/*  1823 - 16 LEDs controlled by two 595 shift registers
 * 
 * This sketch shows you how to drive 16 outputs (connected to LEDs) using three digital
 * pins on the Arduino. This is done with the help of two 595 shift registers.
 * 
 * The sketch causes the LEDs to light up randomly.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 16 x 330 Ohm resistor for the LEDs
 *  - 16 x LEDs
 *  - 2 x 74HC595 shift registers
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
*  Arduino Uno and both 74HC959:
 *  
 *  Arduino Uno   |     74HC959
 *  ------------------------------
 *        5V      |       16
 *        GND     |       8
 *        8       |       14 (only for the first shift register)
 *        9       |       12
 *        10      |       11
 *        
 *        
 *  74HC959 and LEDs:
 *  
 *  For each shift register IC, connect 595 pins 1 to 7 and 15 to the LEDS via their current limiting resistors.
 *     
 *  Connect pin 9 (bit overflow) of the first shift register to pin 14 (serial data input) of the seconde shift register.
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
  byte randNumber2 = random(255);
  writeLeds(randNumber1);
  writeLeds(randNumber2);
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


