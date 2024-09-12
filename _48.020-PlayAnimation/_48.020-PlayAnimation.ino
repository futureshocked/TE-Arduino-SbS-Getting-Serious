/*
  Play Animation

  Sketch shows animation defined in animation.h

  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix
*/



#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "arrow.h"            //Include animation.h header file
#include "block.h"

// Create an instance of the ArduinoLEDMatrix class
ArduinoLEDMatrix matrix;  

void setup() {
  // you can also load frames at runtime, without stopping the refresh
  matrix.loadSequence(arrow);
  matrix.begin();
  
  matrix.play(false); // use false to play only once
}

void loop() {
  delay(1000);
  matrix.loadSequence(block);
  matrix.play(false);
  delay(1000);
  matrix.loadSequence(arrow);
  matrix.play(false);
}
