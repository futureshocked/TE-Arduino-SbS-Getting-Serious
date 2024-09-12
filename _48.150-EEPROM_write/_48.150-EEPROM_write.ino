/*
  EEPROM Write
  
  Stores values read from analog input 0 into the EEPROM.
  These values will stay in the EEPROM when the board is
  turned off and may be retrieved later by another sketch.
 
  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/eeprom
 */

#include <EEPROM.h>

int addr = 10;

void setup() {
  Serial.begin(9600);
  int val = 123;
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  EEPROM.write(addr, val);
  Serial.print("Written at address ");
  Serial.print(addr);
  Serial.print(" value ");
  Serial.print(val, DEC);
  Serial.println();
}

void loop() {
}
