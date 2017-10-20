/*  1310b - RF422 transmitter
 *   
 * This sketch will transmit the "hello" message to the receiver, using 
 * a low-cost 422Mhz radio module.
 * 
 * 
 * 
 * This sketch was adapted by Peter Dalmaris for Arduino Step by Step from the 
 * original that ships with the Radiohead library.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - 433MHz transmitter XY-FST
 *  - Jumper wires
 *  - 1 x LED
 *  - 1 x 330 Ohm resistor
 *  
 *  Libraries
 *  ---------
 *  - VirtualWire
 *
 * Connections
 * -----------
 * Arduino Uno and XY-FST:
 *  
 *  Arduino Uno   |      XY-FST
 *  ------------------------------
 *        5V      |       VCC
 *        GND     |       GND
 *        12      |       RX
 *               
 *  For documentation, please see http://www.airspayce.com/mikem/arduino/RadioHead/index.html        
 *  
 *  Created on October 20 2017 by Peter Dalmaris, Tech Explorations, txplore.com
 * 
 */
// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

const int ledPin = 7;
const int tx_pin = 12;

// Create the transmitter object.
// Even though this example ciruit only includes a transmitter, we still
// need to provide a pin allocation for the receiver. In the example,
// I allocate pin 12 to the receiver and transmitter in order to not
// waste an Arduino pin that will not actually be used. If you decide
// to attach a receiver, change the receiver pin to the actual pin used
// by the receiver. 
// The constructor parameters are:
// speed, rxPin, txPin, pttPin, and pttInverted (see documentation for 
// description of pin roles).
RH_ASK driver(2000, 12, tx_pin, 10); 

void setup()
{
    Serial.begin(9600);  // Debugging only
    
    if (!driver.init())
         Serial.println("init failed");

    pinMode(ledPin, OUTPUT);

    // set initial LED state
    digitalWrite(ledPin, LOW);

    Serial.println("Transmitter started");   
}

void loop()
{
    const char *msg = "hello";
    Serial.println("t");
    digitalWrite(ledPin, HIGH); // Flash a light to show transmitting
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(ledPin, LOW);
    Serial.println("x");
    delay(500);
}
