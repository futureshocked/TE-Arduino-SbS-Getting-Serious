/*  0933 - servo motor dance
 * 
 * This sketch shows you how to control two small 5V servo motors connected directly to the Arduino.
 * 
 * The sketch makes the arm of the servo motors to move to angles stored in an array.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - One or two hobby servo motors
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
 * Yellow wire: One motor's to Arduino pin 9, and the other motor's to Arduino pin 10.
 * 
 * For the breadboard:
 * Connect the external power supply. The GND wire goes to the breadboard's "-" power rail. The 5V 
 * wire goes to breadboard's "+" power rail.
 * Connect a small electrolitic capacitor directly onto the power rail if you notice your servos
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
 
Servo myservo1, myservo2;  // create servo object to control a servo 
                           // a maximum of eight servo objects can be created 
 
int pos_index = 0;    
int const total_positions = 10;
int servo_positions[total_positions] = 
    {156, 79, 88, 152, 34, 144, 28, 174, 117, 27};
 
void setup() 
{ 
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(10);
} 
 
void loop() 
{ 
for (pos_index = 0; pos_index <= total_positions; pos_index += 1) { // goes through the contents of the array
    // in steps of 1 degree
    myservo1.write(servo_positions[pos_index]);    // tell servo 1 to go to new position
    delay(100);                                    // Insert small delay to give servo 1 a head start
    myservo2.write(servo_positions[pos_index]);    // tell servo 2 to go to new position
    delay(400);                                    // wait for servo 2 to reach the position
  }

} 
