/*  0755 - Seven segment clock display timer
 * 
 * This sketch shows you how to use a clock seven segment display to
 * implement a simple timer. The display is used to display the 
 * amount of time in minutes and seconds that has elapsed since the
 * sketch started running on the Arduino.
 * 
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 5 x 330 Ohm resistor for the 4 digits and 1 colon
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SevSeg
 *
 * Connections
 * -----------
 *  Connect display pins for digits 1, 2, 3, 4 to
 *  Arduino pins 2, 3, 4, 5.
 *  
 *  Connect pins for segments A, B, C, D, E, F, G, DT to
 *  Arduino pins 6, 7, 8, 9, 10, 11, 12, 13.
 *  
 *  If you want to display the divider LED (":") of the 
 *  display, connect its anode to Arduino's 5V pin, and the
 *  cathode to Arduino's GND pin, via a 330 Ohm resistor.
 * 
 *  
 *  
 *  Created on May 14 2017 by Peter Dalmaris
 * 
 */
 
#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object
unsigned long timer = 0;

long previousMillis = 0;        // will store last time LED was updated
 
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)

/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN) 

void setup() {

  byte numDigits = 4;   
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // Use 'false' if on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(10); 
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    timer++;
  }

  printTimer();  
}

void printTimer()
{
  int minutes = numberOfMinutes(timer);
  int seconds = numberOfSeconds(timer);
  sevseg.setNumber(minutes*100 + seconds,2);
  sevseg.refreshDisplay(); // Must run repeatedly
}
