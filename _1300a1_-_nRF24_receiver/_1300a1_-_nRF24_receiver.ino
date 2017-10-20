/*  1300a1 - nRF24 Receiver
 *   
 * This sketch shows how to create a simple receiver using the nRF24 module.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - nRF24L01+
 *  - 470 uF capacitor
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SPI
 *  - RF24
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
 *  
 *  Connect the capacitor between the GND and 3.3V pins (beware of the polarity).
 *        
 *        
 *  Created on October 19 2017 by Peter Dalmaris, Tech Explorations, txplore.com
 * 
 */

#include <SPI.h>
#include "RF24.h"

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
  Serial.begin(9600);
  
  radio.begin();  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();  
  Serial.println("Listening");
}

void loop()
{
    // if there is data ready
    if ( radio.available() )
    {
      Serial.print("Receiver.");
      char transmission;
      bool done = false;
      // Fetch the payload, and see if this was the last one.
      radio.read( &transmission, 1 );

      // Spew it
      Serial.print("Received from transmitter:");
      Serial.println(transmission);
 
  // Delay just a little bit to let the other unit
  // make the transition to receiver
  delay(20);
      

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      byte response = B0;
      radio.write( &response, sizeof(response) );
      Serial.println("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      radio.startListening();

    }  
  
}
