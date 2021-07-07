/*  0635 - How to use a Joystick + button module
 * 
 * This sketch shows you how to to a joystick module. 
 * 
 * The module can produce values for the X and Y axes, 
 * plus a 1/0 value for the button.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno.
 *  - a joystick module.
 *  - jumper wires.
 *  - An LED with a 330Ohm resistor.
 *  
 *  Libraries
 *  ---------
 *  None
 *
 * Connections
 * -----------
 *  
 * For the joystick:
 * 
 * Arduino    |     Joystick
 * -------------------------
 *    GND     |       GND
 *    5V      |       +5V
 *    A0      |       VRx
 *    A1      |       VRy
 *    A2      |       SW
 *    
 * 
 * For the LED: 
 * 
 * Connect the anode of the LED (long pin) to Arduino 
 * digital pin 7, a 220 Ω resistor to the LED’s cathode (short pin) 
 * and the other pin of the resistor to Arduino GND.
 *     
 * 
 *  Created on July 7 2021 by Peter Dalmaris
 * 
 */

const byte x_pin = A0;
const byte y_pin = A1;
const byte button_pin = A2;
const byte led_pin = 7;

int x;
int y;
int b;

void setup() {
  pinMode(button_pin, INPUT);
  digitalWrite(button_pin, HIGH);  // Enable the internal pull-up resistor
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the joystick inputs
  x = analogRead(x_pin);
  y = analogRead(y_pin);
  b = digitalRead(button_pin);

  // print out the values captured above
  Serial.print("x=");
  Serial.print(x);
  Serial.print("\t y=");
  Serial.print(y);
  Serial.print("\t button=");
  Serial.print(b);
  Serial.println();
  digitalWrite(led_pin, !b);

  delay(10);
}
