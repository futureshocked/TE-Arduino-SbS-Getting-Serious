


#include <Servo.h> 
 
Servo myservo1, myservo2;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(10);
} 
 
 
void loop() 
{ 

//  If you are using a continuous rotation servo, try these experiments
//  myservo.write(90);   // At this position, the servo does not move. 90 degrees is the resting value
//  myservo.write(100);   // At this position, the servo will move slowly clockwise
//  myservo.write(145);   // At this position, the servo will move faster clockwise
//  myservo.write(180);   // At this position, the servo will move at max speed clockwise
//  myservo.write(80);   // At this position, the servo will move at slowly anti-clockwise
//  myservo.write(70);   // At this position, the servo will move at faster anti-clockwise
//  myservo.write(0);   // At this position, the servo will move at max speed anti-clockwise

// If you are using a normal 180-degree servo, try the following. 
//The code below sweeps the servo from 0 degrees to 180 degrees
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo 1 to go to position in variable 'pos'
    myservo2.write(pos);              // tell servo 2 to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo 1 to go to position in variable 'pos'
    myservo2.write(pos);              // tell servo 2 to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

// You can set the position of a servo , and hold it.
  myservo1.write(0); //Start at position 0
  myservo2.write(180); //Start at position 0
  delay(1000); //Wait for a sec
  myservo1.write(180); //Start at position 180
  myservo2.write(0); //Start at position 180
  delay(1000); //Wait for a sec
} 
