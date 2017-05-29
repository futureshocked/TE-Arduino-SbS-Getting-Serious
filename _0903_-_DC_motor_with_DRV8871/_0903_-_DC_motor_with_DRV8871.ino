/*  0903 - simple DC motor control with the DRV8871 controller IC
 * 
 * This sketch shows you how to control a small 5V DC motor using the DRV8871 controller
 * breakout.
 * 
 * The sketch speeds up the motor in three steps towards one direction,
 * and then does the same in the other direction.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a DRV8871 motor controller breakout
 *  - a small 5V DC motor
 *  
 *  Libraries
 *  ---------
 *  None
 *
 * Connections
 * -----------
 *  
 * Arduino   |   DRV8871 
 * ---------------------
 *   GND     |   GND
 *   5       |   IN1
 *   4       |   IN2
 *           |   MOTOR1 --> Motor wire 1
 *           |   MOTOR1 --> Motor wire 2
 *           |   POWER+ --> 5V power supply 
 *           |   POWER- --> GND power supply
 *     
 * More information:
 *
 * More about the Adafruit DRV8871: https://www.adafruit.com/product/3190
 * DRV8871 datasheet: http://www.ti.com/lit/ds/symlink/drv8871.pdf
 *  
 *  Created on May 28 2017 by Peter Dalmaris
 * 
 */

int speed1     = 5; //Controls speed (PWM) 
int direction1 = 4; //Controls direction
   
bool direction = HIGH;  // Start the motor by moving it towards one direction. Whether it is
                        // clockwise or anticlockwise depends on how you have connected the 
                        // motor's coil.
 
void setup() 
{ 
    pinMode(direction1, OUTPUT);  
    pinMode(speed1, OUTPUT);  
} 
 
void loop() 
{ 
  
    digitalWrite(direction1,direction);   // Direction control
    analogWrite(speed1, 100);             //PWM Speed Control
    delay(1000); 
    analogWrite(speed1, 155);             //PWM Speed Control
    delay(1000); 
    analogWrite(speed1, 255);             //PWM Speed Control
    delay(1000); 
    
    direction = !direction;               //switch direction
    analogWrite(speed1, 0);               // Stop the motor before starting again
}


