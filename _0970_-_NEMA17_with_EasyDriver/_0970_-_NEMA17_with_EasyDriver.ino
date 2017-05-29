/*  0970 - NEMA17 JK42HS40 stepper motor with Easydriver
 * 
 * 
 * This sketch shows how to control a JK42HS40 stepper motor using the 
 * EasyDriver. It is a bare-minimal sketch, in which no library is used.
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
 *  - none
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

 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */
 int direction_pin = 8;
 int step_pin      = 9;

void setup() {                
  pinMode(direction_pin, OUTPUT);     
  pinMode(step_pin, OUTPUT);
  digitalWrite(direction_pin, LOW);
  digitalWrite(step_pin, LOW);
}

void loop() {
  digitalWrite(direction_pin, LOW);  

  //Move the shaft 1600 microsteps towards one direction.
  //By default, the Easydrivers uses 1/8th microsteps. This means that it generates 8
  //microsteps for each actual stepper step. Because the JK42HS40 requires 200 steps
  //for each full rotation (1.8" per step), 200*8 = 1600 microsteps per rotation.
  //This is why I have selected 1600 as the value in the "for" loop below.
  for (int i=0;i<1600;i++)
  {
    //To execute a step (or in this case, a microstep), toggle the step_pin HIGH/LOW.
    //You can control the speed by the amount of delay you insert in the toggle.
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(200);       // Use delayMicroseconds instead of "delay" in order
                                  // to make the motor move faster.
    digitalWrite(step_pin, LOW); 
    delayMicroseconds(200);          
  }
  digitalWrite(direction_pin, HIGH);  

  //Move the shaft 1600 microsteps towards the opposite direction.
  for (int i=0;i<1600;i++)
  {
    //To execute a step (or in this case, a microstep), toggle the step_pin HIGH/LOW.
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(500);          
    digitalWrite(step_pin, LOW); 
    delayMicroseconds(500);          
  }
}
