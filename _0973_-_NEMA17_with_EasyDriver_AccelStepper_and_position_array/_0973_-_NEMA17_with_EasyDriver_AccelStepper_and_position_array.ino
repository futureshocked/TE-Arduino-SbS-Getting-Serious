/*  0973 - NEMA17 JK42HS40 stepper motor with Easydriver and AccelStepper
 * 
 * This sketch shows how to use positions stored in an array to control
 * the movement of the JK42HS40 stepper motor using Easydriver and AccelStepper.
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

int current_position = 0; // We'll use this variable to keep track of the current position
int total_positions = 6;  // Total positions in the positions_to_go array.
int positions_to_go[6] = 
  { 1000,
    -1000,
    2000,
    -1500,
    1500,
    500 }; // An arbitrary set of positions for the motor to go to

 
// Define a stepper and the pins it will use
AccelStepper stepper( AccelStepper::DRIVER, step_pin, direction_pin);

void setup()
{  
  Serial.begin(9600);
  stepper.setMaxSpeed(5000);
  stepper.setAcceleration(5000);
}

void loop()
{
  if (stepper.distanceToGo() == 0) {           // If position reached...
    Serial.println(current_position);
    stepper.moveTo(positions_to_go[current_position++]); // Go back to the opposite position  
  }
  stepper.run();  
    
    if (current_position == total_positions)     // If motor has visited all positions, reset
      {  current_position = 0;                  // the counter
         delay(1000);                              // Wait for 1sec before restarting.
      }                              
}
