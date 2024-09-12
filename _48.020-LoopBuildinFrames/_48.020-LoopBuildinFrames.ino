#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library

ArduinoLEDMatrix matrix;          // Create an instance of the ArduinoLEDMatrix class

void setup() {
  matrix.begin();                 // Initialize the LED matrix
}

void loop() {
  // Load and display the various frame on the LED matrix
  matrix.loadFrame(LEDMATRIX_RESISTOR);
  delay(1000);
  // matrix.clear();
  // delay(100);
  matrix.loadFrame(LEDMATRIX_CHIP);
  delay(1000);
  // matrix.clear();
  // delay(100);
  matrix.loadFrame(LEDMATRIX_LIKE);
  delay(1000);
  // matrix.clear();
  // delay(100);
}