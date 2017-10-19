/*  1240a - Adafruit Bluefruit Reset
 * 
 * This sketch shows you how to software-reset your Bluefruit LE module. Reseting it 
 * after uploading a new sketch is a good practice as it ensures that the module
 * will start executing your sketch from a known good working state.
 * 
 * This sketch uses software serial connection between the module and the Arduino.
 * Please see below for wiring information.
 * 
 * Once you have the connections completed, upload this sketch. It will automatically 
 * reset the module without any user interaction. Once the module is reset, you can
 * be confident that it is in good working order and can continue with the other
 * examples.
 * 
 * This sketch was adapted by Peter Dalmaris for Arduino Step by Step from the original
 * sketch that was developed by Adafruit and ships with the Adafruit_BLE library.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit Bluefruit64 BLE
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

#include "Adafruit_BLE.h"
//#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

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
  Serial.begin(115200);
  Serial.println(F("Adafruit Factory Reset Example"));
  Serial.println(F("------------------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("DONE!"));
}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void)
{
}
