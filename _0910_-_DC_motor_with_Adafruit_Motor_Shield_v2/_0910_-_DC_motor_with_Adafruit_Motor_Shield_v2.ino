/*  0910 - simple DC motor control with the Adafruit Motor Shield V2
 * 
 * This sketch shows you how to control two small 5V DC motors using the Adafruit Motor Shield V2.
 * 
 * The sketch speeds up the motor in three steps towards one direction,
 * and then does the same in the other direction.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit Motor Shield V2.
 *  - a small 5V DC motor
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_MotorShield.h
 *  - Adafruit_MS_PWMServoDriver.h
 *
 * Connections
 * -----------
 *  
 * Plug the motor shield on your Arduino.
 * 
 * Connect the motor to the shield's M1 screw terminals.
 * Connect power from an external power supply to the 
 * shield's Power screw terminal.
 *     
 *  More information
 *  ----------------
 *  For more information on the Adafruit Motor Shield library, see https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
 *  
 *  Created on May 28 2017 by Peter Dalmaris
 * 
 */

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2.
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);  // Get handle for motor 1
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);  // Get handle for motor 2
// You can also make another motor on port M2

void setup() {
  AFMS.begin();  // create with the default PWM frequency 1.6KHz
}

void loop() {
//  motor1->run(FORWARD); // Run forward for half a second
//  motor1->setSpeed(50); 
  motor2->run(FORWARD); // Run forward for half a second
  motor2->setSpeed(255); 
  delay(4000);
//  motor1->run(RELEASE); // Run in idle for half a second
  motor2->run(RELEASE); // Run in idle for half a second
  delay(500);
//  motor1->run(BACKWARD); // Run backward for half a second
//  motor1->setSpeed(50); 
  motor2->run(BACKWARD); // Run backward for half a second
  motor2->setSpeed(255); 
  delay(4000);
//  motor1->run(RELEASE); // Run in idle for half a second
  motor2->run(RELEASE); // Run in idle for half a second
  delay(500);
}
