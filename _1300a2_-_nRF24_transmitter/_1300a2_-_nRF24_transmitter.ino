/*  1300a2 - nRF24 Transmitter
 *   
 * This sketch shows how to create a simple transmitter using the nRF24 module.
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

#define BAUDRATE 9600

char message = 'A';

int led_pin = 8;

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
  Serial.begin(BAUDRATE);

  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);  
  radio.printDetails();
}

void loop()
{  
    radio.stopListening();
    Serial.print("Sending:");
    Serial.print(message);
    Serial.print(" ");
    radio.write( &message, 1 );
    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      Serial.println("Failed, response timed out.");
      
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      byte response;
      radio.read( &response, sizeof(response) );
      Serial.print("Transmitter. Received response from receiver:");
      Serial.println(response,BIN);
      
      if (response == B0) 
      {
        digitalWrite(led_pin,HIGH);
        Serial.println("Ok");
      }
      else
      {
        digitalWrite(led_pin,LOW);
        Serial.println("No connection");
      }
    }

    // Try again  later
    delay(150);
  
}
