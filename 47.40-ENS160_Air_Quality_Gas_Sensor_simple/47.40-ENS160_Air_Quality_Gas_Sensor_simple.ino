#include <Wire.h>

#define ENS160_I2C_ADDR 0x53

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(ENS160_I2C_ADDR);
  Wire.write(0x00);  // read gas data
  Wire.endTransmission();

  delay(500);  // wait for measurement to complete

  Wire.requestFrom(ENS160_I2C_ADDR, 2);

  if (Wire.available()) {
    uint16_t gasData = (Wire.read() << 8) | Wire.read();
    Serial.print("Gas concentration: ");
    Serial.print(gasData);
    Serial.println(" ppb");
  }
}