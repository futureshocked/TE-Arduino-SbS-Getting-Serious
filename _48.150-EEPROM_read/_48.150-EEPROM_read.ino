/*
  EEPROM Read

  Reads the value of each byte of the EEPROM and prints it
  to the computer.
  This example code is in the public domain.

  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/eeprom
 */

#include <EEPROM.h>

int address = 10;

byte value;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  value = EEPROM.read(address);
  Serial.print("Read byte at address ");
  Serial.print(address);
  Serial.print(", value is ");
  Serial.print(value, DEC);
  Serial.println();
}

void loop() {
}
