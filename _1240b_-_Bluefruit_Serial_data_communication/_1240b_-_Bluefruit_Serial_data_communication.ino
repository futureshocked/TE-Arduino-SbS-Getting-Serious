/*  1240b - Adafruit Bluefruit LED toggle
 * 
 * This sketch shows you how to use simple UART to control the state of two LEDs, and
 * retrieve the value of a connected photosensor
 * 
 * These are the available commands:
 * 
 * - "a" Turns on LED 1 and off LED 2
 * - "b" Turns on LED 2 and off LED 1
 * - "c" Turns on LED 2 and on LED 1
 * - "d" Turns off LED 1 and off LED 2
 * - "e" Retrieves the value of a photosensor
 * 
 * This sketch uses software serial connection between the module and the Arduino.
 * Please see below for wiring information.
 * 
 * Once you have the connections completed, upload this sketch and open the serial monitor.
 * 
 * This sketch was adapted by Peter Dalmaris for Arduino Step by Step from the original
 * sketch that was developed by Adafruit and ships with the Adafruit_BLE library.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit Bluefruit64 BLE
 *  - 2 x LEDs
 *  - 2 x 330 Ohm resistors
 *  - 1 x photoresistor
 *  - 1 x 10 kOhm resistor
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SoftwareSerial
 *  - Adafruit_BLE
 *  - Adafruit_BluefruitLE_SPI
 *  - Adafruit_BluefruitLE_UART
 *
 * Connections
 * -----------
 * Arduino Uno and Bluefruit BLE:
 *  
 *  Arduino Uno   |   Bluefruit BLE
 *  ------------------------------
 *        -       |       DFU
 *        GND     |       GND
 *        -       |       RTS
 *        5V      |       VIN
 *        9       |       RXI
 *        10      |       TXO
 *        11      |       CTS
 *        12      |       MOD
 *        
 * Connect the anode of the LEDs to Arduino digital pins 6 and 7, and 
 * the cathode to GND via the current limiting resistors.
 * 
 * Connect the photoresistor and the 10 kOhm resistor in series. Connect
 * the junction of the photoresistor and resistor to analog pin A0 on the
 * Arduino. Connect GND and 5V to the other two ends of the 
 * resistor-photoresistor segment (it does not matter which goes where
 * for this example).
 *        
 *  Created on October 18 2017 by Peter Dalmaris
 * 
 */
 
/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Arduino.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define ledPin1 6
#define ledPin2 7


#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    MODE_LED_BEHAVIOUR        LED activity, valid options are
                              "DISABLE" or "MODE" or "BLEUART" or
                              "HWUART"  or "SPI"  or "MANUAL"
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/

// Create the bluefruit object, either software serial...uncomment these lines

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command <-> Data Mode Example"));
  Serial.println(F("------------------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println(F("Then Enter characters to send to Bluefruit"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
  // Check for user input
  char n, inputs[BUFSIZE+1];

  if (Serial.available())
  {
    n = Serial.readBytes(inputs, BUFSIZE);
    inputs[n] = 0;
    // Send characters to Bluefruit
    Serial.print("Sending: ");
    Serial.println(inputs);

    // Send input data to host via Bluefruit
    ble.print(inputs);
  }

  // Echo received data
  while ( ble.available() )
  {
    int c = ble.read();

    Serial.print((char)c);

    // Hex output too, helps w/debugging!
    Serial.print(" [0x");
    if (c <= 0xF) Serial.print(F("0"));
    Serial.print(c, HEX);
    Serial.print("] ");

    if (c != 0x0A)  // If we receive a return character (HEX 0x0A), then don't make any changes
                    // to the LEDs. 
    {
        if (c == 'a')
        {
          Serial.println("Pin 1 ON");
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, LOW);
        } else if (c == 'b')
        {
          Serial.println("Pin 2 ON");
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin1, LOW);
        } else if (c == 'c')
        {
          Serial.println("Pin 2 and 3 ON");
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin1, HIGH);
        } else if (c == 'd')
        {
          Serial.println("Pin 2 and 3 OFF");
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin1, LOW);
        } else if (c == 'e')
        {
          Serial.print("Sensor reading: ");
          Serial.println(analogRead(0));
        }
        
     }
    }
  }

