/*  0636 - How to plot values from a joystick + button module
 * 
 * This sketch shows you how to read X, Y, button values from 
 * a joystick module and graphically plot them.
 * 
 * To plot these values, we use the Plotter library.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno.
 *  - A joystick module.
 *  - Jumper wires.
 *  - An LED with a 330Ohm resistor.
 *  
 *  Libraries
 *  ---------
 *  Plotter, https://github.com/devinaconley/Arduino-Plotter
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
 
#include "Plotter.h"

Plotter p; // create plotter

const byte x_pin = A0;
const byte y_pin = A1;
const byte button_pin = A2;
const byte led_pin = 7;

int x;
int y;
int b;

void setup() {

  pinMode(button_pin, INPUT);
  digitalWrite(button_pin, HIGH);
  pinMode(led_pin, OUTPUT);
  p.Begin(); // start plotter
  //p.AddXYGraph( "XY graph with 1000 points", 1000, "Y", y, "X", x);
  p.AddTimeGraph( "X-Y time graph with 1000 points", 1000, "X", x, "Y", y);
  p.AddTimeGraph( "Button time graph with 1000 points", 1000, "Button", b);
  //p.SetColor( 0, "red");
  p.SetColor( 0, "red", "green");
  p.SetColor( 1, "blue");
}

void loop() {
  // read the joystick inputs
  x = analogRead(x_pin);
  y = analogRead(y_pin);
  b = digitalRead(button_pin);

  // Plot
  p.Plot();
  digitalWrite(led_pin, !b);
  delay(10);
}
