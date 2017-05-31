/*  0940 - Simple continuous rotation servo motor demo
 * 
 * This sketch shows you how to control a continuous rotation 5V servo motor 
 * connected directly to the Arduino.
 * 
 * The sketch makes the servo's arm move continuisly in different speeds.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - One continuous rotation servo motor
 *  - A small electrolitic capacitor
 *  
 *  Libraries
 *  ---------
 *  - Servo (comes with the Arduino IDE)
 *
 * Connections
 * -----------
 *  
 * For the motors:
 * Brown wire: Breadboard's "-" power rail.
 * Red wire: Breadboard's "+" power rail.
 * Yellow wire: Arduino pin 9
 * 
 * For the breadboard:
 * Connect the external power supply. The GND wire goes to the breadboard's "-" power rail. The 5V 
 * wire goes to breadboard's "+" power rail.
 * Connect a small electrolitic capacitor directly onto the power rail if you notice your servo
 * not working properly. Observe the polarity of the capacitor!
 * 
 *     
 *  More information
 *  ----------------
 *  For more information on the servo library, see https://www.arduino.cc/en/reference/servo
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */

#include <Servo.h> 
 
Servo myservo;             // create servo object to control a servo 
                           // a maximum of eight servo objects can be created 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
// Uncomment the following lines, one at a time, to see the effect that each one
// has on the speed and direction of a continuous rotation servo.

  myservo.write(90);    // At this position, the servo does not move. 90 degrees is the resting value
//  myservo.write(100);   // At this position, the servo will move slowly clockwise
//  myservo.write(145);   // At this position, the servo will move faster clockwise
//  myservo.write(180);   // At this position, the servo will move at max speed clockwise
//  myservo.write(80);    // At this position, the servo will move at slowly anti-clockwise
//  myservo.write(70);    // At this position, the servo will move at faster anti-clockwise
//  myservo.write(0);     // At this position, the servo will move at max speed anti-clockwise
} 
