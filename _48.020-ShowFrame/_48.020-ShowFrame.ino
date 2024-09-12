#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const uint32_t triangle[] = {
		0x7e942,
		0xf4264264,
		0x2f7e9000,
};

void setup() {
  matrix.begin();
  matrix.clear();
  matrix.loadFrame(triangle);
}
 
void loop() {
}