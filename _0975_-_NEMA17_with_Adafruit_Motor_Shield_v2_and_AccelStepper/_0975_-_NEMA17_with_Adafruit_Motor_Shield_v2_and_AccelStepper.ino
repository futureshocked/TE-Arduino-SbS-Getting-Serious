/*  0972 - NEMA17 JK42HS40 stepper motor with Adafruit Motor Shield v2 and AccelStepper
 * 
 * This sketch shows how to use the JK42HS40 stepper motor with Adafruit Motor 
 * Shield v2 and AccelStepper. It will make the motor move clockwise and anti-clock wise.
 * 
 * 
 *  
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit Motor Shield v2
 *  - JK42HS40 stepper motor 
 *  
 *  Libraries
 *  ---------
 *  - AccelStepper
 *
 * Connections
 * -----------
 *  
 *  Connect the wire pairs from each of the motor's coils to the screw
 *  terminals marked M1 and M2 on the shield.
 *  
 *  Connect a 12V power source to the screw terminals marked Power. Be careful
 *  to observe the + and - markings.
 *  
 *     
 *  More information
 *  ----------------
 *  Datasheet for NEMA17 JK42HS40 stepper motor: http://jkongmotor.en.made-in-china.com/product/CBZmFsvVKRWd/China-NEMA17-3D-Printer-Stepper-Motor-with-1m-Leading-Wires.html
 *  Adafruit Motor Shield V2: https://www.adafruit.com/product/1438
 *  AccelStepper: http://www.airspayce.com/mikem/arduino/AccelStepper/
 * Adafruit_MotorShield: https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library/blob/master/Adafruit_MotorShield.h
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);

// you can change these to SINGLE, DOUBLE or INTERLEAVE or MICROSTEP!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
}

AccelStepper Astepper1(forwardstep1, backwardstep1); // use functions to step

int pos = 1000;
void setup()
{  
   Serial.begin(9600);           // set up Serial library at 9600 bps
   Serial.println("Stepper test!");
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  Astepper1.setMaxSpeed(1000);
  Astepper1.setAcceleration(100);
  Astepper1.moveTo(pos);
}

void loop()
{  
   if (Astepper1.distanceToGo() == 0)
  {
    delay(500);
    pos = -pos;
    Astepper1.moveTo(pos);
  }
  Astepper1.run();
}
