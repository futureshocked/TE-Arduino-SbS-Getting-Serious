/*  2715 - How to read the RFID tab ID
 * 
 * This sketch shows you how to to read the ID of an
 * RFID tag. 
 * 
 * With this information, this sketch can recognise a 
 * known tag, and use an LED connected to pin 7 to signal
 * success (tag recognised) or failure (tag not recognise).
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - an RFID reader board with the RC522 module 
 *  - a couple of compatible RFID tags.
 *  - An LED with a 220Ohm resistor
 *  
 *  Libraries
 *  ---------
 *  MFRC522.h: https://github.com/miguelbalboa/rfid/
 *
 * Connections
 * -----------
 *  
 * Use the connections table below to connect the RFID reader
 * to your Arduino.
 * 
 * For the LED: Connect the anode of the LED (long pin) to Arduino 
 * digital pin 7, a 220 Ω resistor to the LED’s cathode (short pin) 
 * and the other pin of the resistor to Arduino GND.
 *     
 * 
 *  
 *  Created on July 3 2021 by Peter Dalmaris
 * 
 */

/*

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte my_nuidPICC[4] = {0xE5, 0xC1, 0x6B, 0x76}; // Change these values to match 
                                                // the ID of your tag.

byte indicator_LED_pin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(indicator_LED_pin, OUTPUT);
  digitalWrite(indicator_LED_pin, LOW);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  Serial.println(F("This code scan the MIFARE Classsic NUID."));

}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] == my_nuidPICC[0] &&
      rfid.uid.uidByte[1] == my_nuidPICC[1] &&
      rfid.uid.uidByte[2] == my_nuidPICC[2] &&
      rfid.uid.uidByte[3] == my_nuidPICC[3] ) {
    Serial.println(F("Hello, Peter!"));
    digitalWrite(indicator_LED_pin, HIGH);
    delay(1000);
    digitalWrite(indicator_LED_pin, LOW);
  }
  else {
    Serial.println(F("I do not recognise this card..."));
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(indicator_LED_pin, HIGH);
      delay(100);
      digitalWrite(indicator_LED_pin, LOW);
      delay(100);
    }
  }

  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
