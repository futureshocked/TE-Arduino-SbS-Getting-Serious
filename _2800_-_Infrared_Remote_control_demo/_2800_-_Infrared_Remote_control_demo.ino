/*  ASBSGSR_-_2800_-_Infrared_Remote_control_demo
 * 
 * This sketch Demonstrates receiving NEC IR codes with IRrecv to
 * control a red and a green LED. 
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - an Infrared (IR) receiver and transmitter that are 
 *  - compatible with the Arduino-IRremote library.
 *  - Two LEDs
 *  - Two 330Ohm resistors
 *  - Jumper wires
 *  - Mini breadboard
 *  
 *  Libraries
 *  ---------
 *  Arduino-IRremote: https://github.com/Arduino-IRremote/Arduino-IRremote
 *
 * Connections
 * -----------
 *  
 * For the IR receiver: 
 * 
 * IR Receiver   |    Arduino
 * --------------------------
 *       V+      |      5V
 *       GND     |      GND
 *       OUT     |      2
 * 
 * For the LEDs: Connect the anode of the red LED (long pin) to Arduino 
 * digital pin 7, a 330 Ω resistor to the LED’s cathode (short pin) 
 * and the other pin of the resistor to Arduino GND.
 * 
 * Do the same for the green LED, except that the anode should be 
 * connected to pin 8.
 *     
 *  
 *  Created on July 14 2021 by Peter Dalmaris
 * 
 */

#include <IRremote.h>

#define IR_RECEIVE_PIN 2

decode_results results;
#define RED_PIN 7
#define GREEN_PIN  8

void setup() {
  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    if (IrReceiver.decodedIRData.address == 0) {
      if (IrReceiver.decodedIRData.command == 0x1C) {
        digitalWrite(RED_PIN, HIGH);
        delay(2000);
        digitalWrite(RED_PIN, LOW);
      } else if (IrReceiver.decodedIRData.command == 0x19) {
        digitalWrite(GREEN_PIN, HIGH);
        delay(2000);
        digitalWrite(GREEN_PIN, LOW);
      }
    }

    IrReceiver.resume();
  }
}
