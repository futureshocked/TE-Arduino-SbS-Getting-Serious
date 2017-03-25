/*  0640b - Rotary encoder with interrupts
 * 
 * This sketch shows you how to use a good quality rotary encoder
 * with the use of interrupts. In general, use of
 * interrups result in more accurate output from the encoder, it is
 * possible to use it without interrupts if the appropriate 
 * pins 1 and 2 on the Arduino Uno are already used.
 * 
 * Beware that in the Arduino Uno, the pins on which interrupts can be  
 * enabled are 2 and 3.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a good quality rotary encoder 
 *  
 *  Libraries
 *  ---------
 *  Encoder.h
 *
 * Connections
 * -----------
 *  
 * A rotary encoder has three pins. Some encoders also include
 * a button, so there are two more pins for the button signal.
 * 
 * Of the three encoder pins, connect the common to GND, and the
 * other two pins to any available digital pin on the Arduino.
 * 
 * Refer to the encoder datasheet for the location of the common 
 * pin.
 *     
 * 
 *  
 *  Created on March 21 2017 by Peter Dalmaris
 * 
 */
/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  delay(50);
}
