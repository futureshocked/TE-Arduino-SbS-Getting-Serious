/*  0630 - Membrane potentiometer
 * 
 * This sketch shows you how to use the membrane potentiometer.
 * This device works like a rotary potentiometer, but instead of
 * rotating a knob in order to change its resistance, your apply
 * pressure anywhere on its surface. The out resistance of the
 * device depends on the location of the pressure.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a membrane potentiometer 
 *  
 *  Libraries
 *  ---------
 *  None
 *
 * Connections
 * -----------
 *  
 * Refer to the schematic that is available with this lecture.
 * If the schematic is not available, follow these instructions:
 * 
 * As you are looking at the front of the membrane potentiometer,
 * the pin on the left is 1, the middle is 2, and the right is 3. 
 *     
 *     Arduino |   Potentiometer
 *     --------|----------------
 *        GND  |        1
 *        A0   |        2
 *        5V   |        3
 * 
 *  
 *  Created on March 21 2017 by Peter Dalmaris
 * 
 */


int potPin = A0;    // select the input pin for the potentiometer
int potValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(100);
}
