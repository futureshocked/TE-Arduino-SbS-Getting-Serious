/*  0900 - simple DC motor control with the L293 controller IC
 * 
 * This sketch shows you how to control a small 5V DC motor using the L298N controller
 * breakout.
 * 
 * The sketch speeds up the motor in three steps towards one direction,
 * and then does the same in the other direction.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a L298N motor controller breakout
 *  - a small 5V DC motor
 *  
 *  Libraries
 *  ---------
 *  None
 *
 * Connections
 * -----------
 *  
 * Arduino   |   L298N 
 * ---------------------
 *   GND     |   GND
 *   5       |   IN1
 *   4       |   IN2
 *           |   OUT1  --> Motor wire 1
 *           |   OUT2  --> Motor wire 2
 *           |   +12V  --> 5V power supply 
 *           |   GND   --> GND power supply
 *     
 * 
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


