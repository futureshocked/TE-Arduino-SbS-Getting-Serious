/*  NeoPixel Shield example sketch
 * 
 * This sketch shows you how to draw graphics on an Adafruit NeoPixel shield.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit NeoPixel Shield
 *  
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_GFX
 *  - Adafruit_NeoMatrix
 *  - Adafruit_NeoPixel
 *
 * Connections
 * -----------
 *  
 *  Just plug the shield on your Arduino Uno
 *  
 * 
 * Other information
 * -----------------
 *  Adafruit Neopixels Shield product page: https://www.adafruit.com/products/1430
 *  Color chooser for RGB values: http://www.colorschemer.com/online.html
 *  Adafruit GXF library documentation: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf
 *  Adafruit Neomatrix library: https://github.com/adafruit/Adafruit_NeoMatrix
 *  Adafruit Neopixel library: https://github.com/adafruit/Adafruit_NeoPixel
 *  
 *  Created on April 1 (no joke) 2017 by Peter Dalmaris
 * 
 */


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
      matrix.Color(255, 0, 0),       // RED
      matrix.Color(0, 255, 0),       // GREEN
      matrix.Color(0, 0, 255),       // BLUE
      matrix.Color(255, 255, 255),   // WHITE
      matrix.Color(128,0,255),       // PURPLE
      matrix.Color(0,184,245),       // LIGHT BLUE
      matrix.Color(255,255,0),       // YELLOW
      }; 

//int x    = matrix.width();
//int y    = matrix.height();


void setup() {
    matrix.begin();
   // matrix.setTextWrap(false);
    matrix.setBrightness(40);

  // Fill the matrix with some random colors
  matrix.fillScreen(colors[random(0, 6)]);
  matrix.show();delay(200);
  matrix.fillScreen(colors[random(0, 6)]);
  matrix.show();delay(200);
  matrix.fillScreen(colors[random(0, 6)]);
  matrix.show();delay(200);

  matrix.fillScreen(0);
  matrix.show();delay(200);
  
     // Draw pixels
  matrix.drawPixel(0, 0, colors[0]);
  matrix.show();delay(200);
  matrix.drawPixel(4, 0, colors[1]);
  matrix.show();delay(200);
  matrix.drawPixel(0, 7, colors[2]);
  matrix.show();delay(200);
  matrix.drawPixel(4, 7, colors[3]);
  matrix.show();delay(200);

  // Draw lines
  matrix.drawLine(1, 1, 3, 6, colors[4]);
  matrix.show();delay(200);
  matrix.drawLine(3, 1, 1, 6, colors[5]);
  matrix.show();delay(200);

  // Draw box
  matrix.drawRect(1, 2, 3, 4, colors[6]);
  matrix.show();delay(200);

  delay(2000);
  matrix.fillScreen(0);
  matrix.show();

  // Draw pixels at random locations, random colors
  for (int i = 0; i < 50; i++)
  {
    matrix.drawPixel(random(0, 4), random(0, 7), colors[random(0, 6)]);
    matrix.show();
    delay(100);
    matrix.fillScreen(0);
  }

  matrix.fillScreen(colors[random(0, 6)]);
  matrix.show();
}

void loop() {
 
}
