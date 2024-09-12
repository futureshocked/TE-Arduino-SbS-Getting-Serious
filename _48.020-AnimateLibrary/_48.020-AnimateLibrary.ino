#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library

// Create an instance of the ArduinoLEDMatrix class
ArduinoLEDMatrix matrix;  

void setup() {
    matrix.begin();
    // matrix.loadSequence(LEDMATRIX_ANIMATION_ATMEGA);
    // matrix.play(false);
}

void loop() {
  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  matrix.play(false);
  delay(1000);
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.play(false);
  delay(1000);
  matrix.loadSequence(LEDMATRIX_ANIMATION_ATMEGA);
  matrix.play(false);
  delay(1000);
}