/*  0982 - 28BYJ-48 stepper motor control with the Adafruit Motor Shield v2
 * 
 * This sketch shows you how to control the common 28BYJ-48 (geared) 
 * stepper motor with the Adafruit Motor Shield v2. 
 * It will make the motor move clockwise and anti-clock wise.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit Motor Shield v2
 *  - 28BYJ-48 stepper motor 
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_MotorShield
 *
 * Connections
 * -----------
 *  
 *  Connect the wire pairs from each of the motor's coils to the screw
 *  terminals marked M1 and M2 on the shield.
 *  
 *  Connect a 5V power source to the screw terminals marked Power. Be careful
 *  to observe the + and - markings.
 *  
 *     
 *  More information
 *  ----------------
 *  28BYJ-48 datasheet: http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/07/Stepper-Motor-28BJY-48-Datasheet.pdf
 *  Adafruit Motor Shield V2: https://www.adafruit.com/product/1438
 *  Adafruit_MotorShield: https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library/blob/master/Adafruit_MotorShield.h
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */


#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a 28BYJ-48, 5V stepper motor with 64*64 steps per revolution
// to motor port #1 (M1 and M2)
// The motor needs 64 steps for a full internal shaft revolution. The gear reduction 
// mechanism reduces that by 64, so that the total internal steps for a full
// revolution is 64 * 64 = 4096.
Adafruit_StepperMotor *myMotor = AFMS.getStepper(64*64, 1); 


void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(100);  // 10 rpm   
}

void loop() {
  // You can change the second parameter to SINGLE, DOUBLE or INTERLEAVE or MICROSTEP!
  myMotor->step(1000, FORWARD, SINGLE); 
  delay(250);
  myMotor->step(1000, BACKWARD, SINGLE);
  delay(500);
}
