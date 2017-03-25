/*  0640a - Rotary encoder without interrupts
 * 
 * This sketch shows you how to use a good quality rotary encoder
 * without the use of interrupts. Although, in general, use of
 * interrups result in more accurate output from the encoder, it is
 * possible to use it without interrupts if the appropriate 
 * pins 1 and 2 on the Arduino Uno are already used.
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

/* Encoder Library - NoInterrupts Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

// If you define ENCODER_DO_NOT_USE_INTERRUPTS *before* including
// Encoder, the library will never use interrupts.  This is mainly
// useful to reduce the size of the library when you are using it
// with pins that do not support interrupts.  Without interrupts,
// your program must call the read() function rapidly, or risk
// missing changes in position.
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

// Beware of Serial.print() speed.  Without interrupts, if you
// transmit too much data with Serial.print() it can slow your
// reading from Encoder.  Arduino 1.0 has improved transmit code.
// Using the fastest baud rate also helps.  Teensy has USB packet
// buffering.  But all boards can experience problems if you print
// too much and fill up buffers.

// Change these two numbers to the pins connected to your encoder.
//   With ENCODER_DO_NOT_USE_INTERRUPTS, no interrupts are ever
//   used, even if the pin has interrupt capability
Encoder myEnc(5, 6);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic NoInterrupts Test:");
}

long position  = -999;

void loop() {
  long newPos = myEnc.read();
  if (newPos != position) {
    position = newPos;
    Serial.println(position);
  }
  // With any substantial delay added, Encoder can only track
  // very slow motion.  You may uncomment this line to see
  // how badly a delay affects your encoder.
  delay(50);
}
