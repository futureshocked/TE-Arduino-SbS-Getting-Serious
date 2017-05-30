/*  0972 - NEMA17 JK42HS40 stepper motor with Easydriver and AccelStepper
 * 
 * 
 * This sketch shows how to control a JK42HS40 stepper motor using the 
 * EasyDriver. In this sketch, we use the AccelStepper library in order
 * to not block the rest of the sketch while the rotor is moving.
 * 
 * The sketch spins up the motor towards one direction, and then towards 
 * the other.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Easydriver breakout
 *  - JK42HS40 stepper motor 
 *  
 *  Libraries
 *  ---------
 *  - AccelStepper
 *
 * Connections
 * -----------
 *  
 * Arduino   |   Easydriver breakout
 * ------------------------------
 *      9    |    STEP
 *      8    |    DIR
 *      GND  |    GND (adjucent to STEP and DIR)
 *           |    GND (PWR IN) to power supply GND
 *           |    M+  (PWR IN) to power supply 12V
 *           |    MOTOR A pair to motor coil 1
 *           |    MOTOR B pair to motor coil 2
 *     
 *  More information
 *  ----------------
 *  Datasheet for NEMA17 JK42HS40 stepper motor: http://jkongmotor.en.made-in-china.com/product/CBZmFsvVKRWd/China-NEMA17-3D-Printer-Stepper-Motor-with-1m-Leading-Wires.html
 *  Easydriver: http://www.schmalzhaus.com/EasyDriver/
 *  AccelStepper: http://www.airspayce.com/mikem/arduino/AccelStepper/

 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */
 
#include <AccelStepper.h>

int direction_pin = 8;
int step_pin      = 9;
 
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, step_pin, direction_pin);

int pos = 5000;

void setup()
{  
  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(1000);
  stepper.setSpeed(5000);
}

void loop()
{
  if (stepper.distanceToGo() == 0)
  {    
    delay(500);
    pos = -pos;
    stepper.moveTo(pos);
  }
  stepper.run();
}
