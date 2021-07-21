/*
   ASBSGSR_-_2800_-_Infrared_Remote_control_demo

   Demonstrates receiving NEC IR codes with IRrecv to
   control a red and a green LED.
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
