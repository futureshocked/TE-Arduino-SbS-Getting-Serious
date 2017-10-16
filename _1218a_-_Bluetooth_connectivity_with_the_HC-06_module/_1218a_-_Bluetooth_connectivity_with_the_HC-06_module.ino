/*  1218a - Bluetooth connection demo with the HC-06
 * 
 * This sketch shows you how to control an LED from the serial monitor
 * using a wireless serial connection with the HC-06 module.
 * 
 * Once you have the connections completed, with the HC-06 not powered, upload 
 * this sketch via the USB cable. Then disconnect the USB cable, and power up the 
 * HC-06. Connect the HC-06 to your computer as you do with any Bluetooth device.
 * The pairing key is "1234". 
 * 
 * In the Arduino IDE, select the HC-06 from the list of available devices. Then,
 * start the serial monitor. Ensure that there is no line ending in the monitor.
 * In the input field, type "H" to turn the LED on, and press Enter. The LED should
 * turn on. Send any other character to turn off the LED.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 1 x 330 Ohm resistor for the LED
 *  - 1 x LED
 *  - 1 x HC-06 Bluetooth module
 *  - An external power supply for the Arduino
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
*  Arduino Uno and HC-06:
 *  
 *  Arduino Uno   |     HC-06
 *  ------------------------------
 *        5V      |       VCC
 *        GND     |       GND
 *        1       |       RXD
 *        2       |       TXD
 *        
 * Coneect the 330 Ohm  resistor in series with the LED. 
 * 
 * Connect the anode of the LED to Arduino digital pin 8, and 
 * its cathode to GND.
 *        
 *  Created on October 16 2017 by Peter Dalmaris
 * 
 */
 
char val;       // variable to receive data from the serial port
int ledpin = 8; // LED connected to pin 8

void setup() {

  pinMode(ledpin, OUTPUT);  // pin 8 as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
}

void loop() {

  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
} 
