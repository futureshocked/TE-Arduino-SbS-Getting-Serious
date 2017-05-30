/*  0952 - NEMA17 JK42HS40 stepper motor with L298N motor controller
 * 
 * This is a very simple example of how to control the NEMA17 stepper motor
 * using the L298N motor controller and the Stepper library. This library comes
 * with the Arduino IDE.
 * 
 * The example makes the rotor move one full rotation in both directions.
 *  
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - L298N motor controller
 *  - JK42HS40 stepper motor 
 *  
 *  Libraries
 *  ---------
 *  - Stepper.h
 *
 * Connections
 * -----------
 *  
 * Arduino   |   L298N breakout
 * ------------------------------
 *      8    |    IN1
 *      9    |    IN2
 *      10   |    IN3
 *      11   |    IN4
 *      GND  |    GND
 *           |    GND to power supply GND
 *           |    12V to power supply 12V
 *     
 *  More information
 *  ----------------
 *  Datasheet for NEMA17 JK42HS40 stepper motor: http://jkongmotor.en.made-in-china.com/product/CBZmFsvVKRWd/China-NEMA17-3D-Printer-Stepper-Motor-with-1m-Leading-Wires.html
 *  L298N breakout: http://www.ti.com/lit/ds/symlink/l293.pdf
 *  Stepper library: https://www.arduino.cc/en/reference/stepper
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */
 

/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(100);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-100);
  delay(500);
}

