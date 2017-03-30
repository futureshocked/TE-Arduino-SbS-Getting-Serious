/*  Adafruit 2.8" color TFT with SD card and touch
 * 
 * This sketch shows you how to use the the Adafruit 2.8" color
 * TFT display, with SD card module and resistive touch interface.
 * 
 * The sketch loads a bitmap image that makes up the user interface.
 * It contains three graphical buttons and two areas where text
 * is printed. When the user presses one of the buttons, the ID
 * of that button is displayed in one of the text areas.
 * 
 * With every touch, the touch coordinates are printed in the
 * second text area.
 * 
 * This sketch is based on examples written by Limor Fried/Ladyada 
 * for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit 2.8" TFT Touch Shield v2 - Resistive
 *  
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_GFX.h
 *  - Adafruit_ILI9341.h
 *  - SPI.h
 *  - Wire.h
 *  - SD.h
 *  - Adafruit_STMPE610.h
 *
 * Connections
 * -----------
 *  The TFT screen comes as a shield. Just plug the shield on the
 *  Arduino Uno and connect to your computer via USB.
 *  
 * 
 * Other information
 * -----------------
 *  For information on the SD card library: https://github.com/adafruit/SD
 *  For information on the Adafruit GFX library: https://learn.adafruit.com/adafruit-gfx-graphics-library/overview
 *  For information on the Adafruit ILI9341 (TFT) library: https://github.com/adafruit/Adafruit_ILI9341/
 *  For information on the Adafruit STMPE610 (touch) library: https://github.com/adafruit/Adafruit_STMPE610
 *  
 *  
 *  Created on March 29 2017 by Peter Dalmaris
 * 
 */

/***************************************************
  This is an example for the Adafruit STMPE610 Resistive
  touch screen controller breakout
  ----> http://www.adafruit.com/products/1571

  Check out the links above for our tutorials and wiring diagrams
  These breakouts use SPI or I2C to communicate

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9341.h" // Hardware-specific library
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "Adafruit_STMPE610.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 touch = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define SD_CS 4

void setup() {
  Serial.begin(9600);

  tft.begin();

  if (!touch.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }
  Serial.println("OK!");

  bmpDraw("demont.bmp", 0, 0);  // Draw the background image
                                // This makes up the user interface
}
//uint16_t last_x = 3000, last_y = 500;
int button_1_pressed = 0;

void loop() {
  // See if there's any  touch data for us
  if (touch.bufferEmpty()) {
    return;
  }
  // Retrieve a point
  TS_Point p = touch.getPoint();
  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.print(p.x); Serial.print(" "); Serial.println(p.y);

  if (p.x < 280 && p.x > 210)
  {
    //Format the text for the button press notifications
    tft.setCursor(165, 120);
    tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);    
    tft.setTextSize(4);
    tft.setRotation(1);
   
    //Go in this block if button 1 is pressed
    if (p.y > 10 && p.y < 70)
    {
      Serial.println("Button 1 pressed");
      tft.println(" 1 ");
    }

    //Go in this block if button 2 is pressed
    if (p.y > 75 && p.y < 135)
    {
      Serial.println("Button 2 pressed");
      tft.println(" 2 ");
    }
    //Go in this block if button 2 is pressed
    if (p.y > 135 && p.y < 205)
    {
      Serial.println("Button 3 pressed");
      tft.println(" 3 ");
    }
  }

  //Print the last touch coordinates to the screen
  tft.setCursor(130, 190);
  tft.setTextColor(ILI9341_RED, ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.print("        ");
  tft.setCursor(130, 190);
  tft.print(p.x); tft.print(",");
  tft.print(p.y);

}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, int16_t x, int16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col, x2, y2, bx1, by1;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if ((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        x2 = x + bmpWidth  - 1; // Lower-right corner
        y2 = y + bmpHeight - 1;
        if ((x2 >= 0) && (y2 >= 0)) { // On screen?
          w = bmpWidth; // Width/height of section to load/display
          h = bmpHeight;
          bx1 = by1 = 0; // UL coordinate in BMP file
          if (x < 0) { // Clip left
            bx1 = -x;
            x   = 0;
            w   = x2 + 1;
          }
          if (y < 0) { // Clip top
            by1 = -y;
            y   = 0;
            h   = y2 + 1;
          }
          if (x2 >= tft.width())  w = tft.width()  - x; // Clip right
          if (y2 >= tft.height()) h = tft.height() - y; // Clip bottom

          // Set TFT address window to clipped image bounds
          tft.startWrite(); // Requires start/end transaction now
          tft.setAddrWindow(x, y, w, h);

          for (row = 0; row < h; row++) { // For each scanline...

            // Seek to start of scan line.  It might seem labor-
            // intensive to be doing this on every line, but this
            // method covers a lot of gritty details like cropping
            // and scanline padding.  Also, the seek only takes
            // place if the file position actually needs to change
            // (avoids a lot of cluster math in SD library).
            if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
              pos = bmpImageoffset + (bmpHeight - 1 - (row + by1)) * rowSize;
            else     // Bitmap is stored top-to-bottom
              pos = bmpImageoffset + (row + by1) * rowSize;
            pos += bx1 * 3; // Factor in starting column (bx1)
            if (bmpFile.position() != pos) { // Need seek?
              tft.endWrite(); // End TFT transaction
              bmpFile.seek(pos);
              buffidx = sizeof(sdbuffer); // Force buffer reload
              tft.startWrite(); // Start new TFT transaction
            }
            for (col = 0; col < w; col++) { // For each pixel...
              // Time to read more pixel data?
              if (buffidx >= sizeof(sdbuffer)) { // Indeed
                tft.endWrite(); // End TFT transaction
                bmpFile.read(sdbuffer, sizeof(sdbuffer));
                buffidx = 0; // Set index to beginning
                tft.startWrite(); // Start new TFT transaction
              }
              // Convert pixel from BMP to TFT format, push to display
              b = sdbuffer[buffidx++];
              g = sdbuffer[buffidx++];
              r = sdbuffer[buffidx++];
              tft.writePixel(tft.color565(r, g, b));
            } // end pixel
          } // end scanline
          tft.endWrite(); // End last TFT transaction
        } // end onscreen
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
