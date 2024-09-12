// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();
  // add some static text
  // will only show "UNO" (not enough space on the display)
  const char text[] = "UNO R4 Wifi";
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  //matrix.endText();
  matrix.endText(SCROLL_LEFT);
  delay(2000);
}

void loop() {
  matrix.textScrollSpeed(50);
  const char text[] = "    Hello World!    ";
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
}