/*  1300c - nRF24 Node 2
 *   
 * This node has an LED, and a photoresistor. When it receives a message (trigger) from
 * Node 1, it will turn on the LED for 500ms and respond with the value of the photo-resistor.
 * 
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - nRF24L01+
 *  - 470 uF capacitor
 *  - 1 x LED
 *  - 1 x 330 Ohm resistors
 *  - 1 x photoresistor
 *  - 1 x 10 kOhm resistor
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SPI
 *  - RF24
 *  - LiquidCrystal_I2C
 *
 * Connections
 * -----------
 * Arduino Uno and nRF24 (consult the schematic diagram as most
 * nRF24 modules don't include any pin markings):
 *  
 *  Arduino Uno   |      nRF24
 *  ------------------------------
 *        -       |       IRQ
 *        11      |       MOSI
 *        10      |       CSN
 *        5V      |       VCC
 *        GND     |       GND
 *        9       |       CE
 *        13      |       SCK
 *        12      |       MISO
 *        
 *  Connect the LED anode to digital pin 7 and the cathod via the 330 Ohm resistor
 *  to GND.
 *  
 *  Connect the photo resistor and 10 kOhm resistor to GND and 5V, and their junction 
 *  to analog pin 0.
 *  
 *  Connect the capacitor between the GND and 3.3V pins (beware of the polarity).
 *        
 *        
 *  Created on October 19 2017 by Peter Dalmaris, Tech Explorations, txplore.com
 * 
 */

#include <SPI.h>
#include "RF24.h"

#define BAUDRATE 9600

const int ledPin = 7;

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
  Serial.begin(BAUDRATE);
  
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, LOW);

  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
  Serial.println("Node 2 ready");
}

void loop()
{

  // if there is data ready
  if ( radio.available() )
  {
    Serial.print("Receiver.");
    char transmission;
    radio.read( &transmission, 1 );
    // Print out the content of "transmission"
    Serial.print("Received from transmitter:");
    Serial.println(transmission);

    // Delay just a little bit to let the other unit
    // make the transition to receiver
    delay(20);

    // First, stop listening so we can talk
    radio.stopListening();

    // Send the final one back.
    int response = analogRead(0);
    radio.write( &response, sizeof(response) );
    Serial.println("Sent response.\n\r");

    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);

    // Now, resume listening so we catch the next packets.
    radio.startListening();

  }

}
