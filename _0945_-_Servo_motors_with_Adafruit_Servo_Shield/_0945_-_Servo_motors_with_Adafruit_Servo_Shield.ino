/*  0945 - Servo motor demo using the Adafruit Servo Shield
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
 *  - One or two hobby servo motors
 *  - The Adafruit Servo Shield
 *  
 *  Libraries
 *  ---------
 *  - Wire (comes with the Arduino IDE)
 *  - Adafruit_PWMServoDriver
 *
 * Connections
 * -----------
 *  
 * For the motors:
 * Connect the motors to the first two servo positions.
 * Connect 5V external power to the power screw terminals (observe the polarity!).
 * 
 * 
 *     
 *  More information
 *  ----------------
 *  For more information on the Adafruit_PWMServoDriver library, see https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 *  For more information on the Adafruit Servo Shield: http://www.adafruit.com/products/815
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */
/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  120 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  560 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
  }
  delay(500);

}
