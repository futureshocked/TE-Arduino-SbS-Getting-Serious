/*  0580 - Magnetic reed switch demo
 * 
 * This sketch shows you how to use a magnetic door reed switch.
 * When the switch is on, an LED connected to digital pin 8 will
 * light up.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a door reed switch 
 *  - 5mm LED
 *  - 250 Ohm resistor for the LED
 *  - 20 kOhm resistor for the switch
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
 * Connect the LED so that its cathode is connected to 
 * the Arduino GND pin, and its anode to the 250 Ohm resistor. The 
 * other pin of the resistor should be connected to the Arduino pin 8.
 * 
 * Connect the one wire from the reed switch to the Arduino 5V pin. The 
 * other wire should go to the Arduino digital pin 7. Connect a 20 kOhm resistor
 * from the reed switch wire that is connected to digital pin 7 to
 * the Arduino GND pin.
 *     
 * 
 *  
 *  Created on March 20 2017 by Peter Dalmaris
 * 
 */

#define led_pin    8
#define switch_pin 7

// variables will change:
int switchState = 0;         // variable for reading the switch status


void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin   , OUTPUT);
  pinMode(switch_pin, INPUT);

}

void loop() {
  // read the state of the pushbutton value:
  switchState = digitalRead(switch_pin);

  // check if the switch is pressed.
  // if it is, the switch is HIGH:
  if (switchState == HIGH) {
    // turn LED on:
    digitalWrite(led_pin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(led_pin, LOW);
  }
}
