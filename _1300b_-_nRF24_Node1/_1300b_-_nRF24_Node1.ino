/*  1300b - nRF24 Node 1
 *   
 *  This node has a, an LED, a button and an LCD. When the button is pressed, the LED goes on,
 *  and a message is send to Node 2. At Node 2, when the message is received an LED blinks for
 *  500msec, then a reading is taken from the photosensor, and the value is sent to Node 1.
 *  When Node 1 receives the value, it displays it on the LCD and turns off the LED.
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
 *  - 3 x 330 Ohm resistors
 *  - 1 x push button
 *  - 1 x 20 kOhm pull-down resistor
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
 *    I2C LCD     |    Arduino Uno
 *  -----------------------------
 *      GND       |      GND
 *      Vcc       |      5V
 *      SDA       |      SDA or A4
 *      SCL       |      SCL or A5
 *        
 *  Connect the LED anode to digital pin 7 and the cathod via the 330 Ohm resistor
 *  to GND.
 *  
 *  Connect the push button with the pull-down resistor to digital pin 2.
 *  
 *  Connect the capacitor between the GND and 3.3V pins (beware of the polarity).
 *        
 *        
 *  Created on October 19 2017 by Peter Dalmaris, Tech Explorations, txplore.com
 * 
 */



#include <SPI.h>
#include "RF24.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define BAUDRATE 9600

// We'll just send the char 'A' to trigger a response from Node 2
char message = 'A';

// constants for the LED and button pins
const int buttonPin = 2;    
const int ledPin = 7;

// Variables for the LED and the button
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
  Serial.begin(BAUDRATE);

  // Setup the pins
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Setup the LCD screen
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  // Setup the nRF24
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
//  radio.printDetails();
  Serial.println("Node 1 ready");
  
}

void loop()
{
  //Get a reading from the button. Using software debounce to avoid rapid
  //ghost button presses
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //          ledState = !ledState;
        digitalWrite(ledPin, HIGH);
        radio.stopListening();
        Serial.print("Sending:");
        Serial.print(message);
        Serial.print(" ");
        radio.write( &message, sizeof(unsigned long) );
        // Now, continue listening
        radio.startListening();
      }
    }
  }

  // Save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

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
    // Get the response and print it to the LCD
    int response;
    radio.read( &response, sizeof(response) );
    Serial.print("Transmitter. Received response from receiver:");
    Serial.println(response);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(response);
    digitalWrite(ledPin, LOW);
  }
  
  // Try again  later
  delay(150);

}
