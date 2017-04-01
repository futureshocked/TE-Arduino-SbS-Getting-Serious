/*  Adafruit 2.2" Color TFT Shield w/microSD
 * 
 * This sketch shows you how to use the the Adafruit 1.8" color
 * TFT display, with SD card module and joystick interface.
 * 
 * The sketch loads a bitmap image that makes up the user interface.
 * The image contains icons that imply the meaning of the data that 
 * is displayed on it.
 * 
 * 
 * This sketch is based on examples written by Limor Fried/Ladyada 
 * for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit 2.2" TFT Shield with SD card module
 *  
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_GFX.h
 *  - Adafruit_ILI9340.h
 *  - SPI.h
 *  - SD.h
 *
 * Connections
 * -----------
 *  
 *  2.2" TFT  |   Arduino Uno 
 *  -------------------------
 *      SCK   |       13
 *      MISO  |       12
 *      MOSI  |       11
 *      CS    |       10
 *      SDCS  |       4
 *      RST   |       8
 *      D/C   |       9
 *      VIN   |       5V
 *      GND   |       GND
 *  
 * 
 * Other information
 * -----------------
 *  For information on the SD card library: https://github.com/adafruit/SD
 *  For information on the Adafruit GFX library: https://learn.adafruit.com/adafruit-gfx-graphics-library/overview
 *  For information on the Adafruit ILI9340 (TFT) library: https://github.com/adafruit/Adafruit_ILI9340
 *  
 *  
 *  Created on April 1 (no joke) 2017 by Peter Dalmaris
 * 
 */
/***************************************************
  This is an example sketch for the Adafruit 1.8" TFT shield with joystick
  ----> http://www.adafruit.com/products/802

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 pins are required to
  interface
  One pin is also needed for the joystick, we use analog 3
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include <SD.h>
#include <SPI.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 4

Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);


void setup(void) {
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("OK!");

  tft.begin();
//  tft.fillScreen(ILI9340_BLUE);
  
  
  bmpDraw("732-UInt.bmp", 0, 0);

  //Print out the time and date
  tft.setTextColor(ILI9340_BLACK);
  tft.setRotation(1);
  tft.setTextSize(2);
  tft.setCursor(85, 20);          //Overwrite any text that might
  tft.print("                ");  //be in this position before
  tft.setCursor(85, 20);          //writting new text
  tft.print("Sat 1 April 2017");
  tft.setCursor(85, 40);          //Overwrite any text that might
  tft.print("                ");  //be in this position before
  tft.setCursor(85, 40);          //writting new text
  tft.print("12:07pm");

  //Print out the temperature
  tft.setTextSize(4);
  tft.setCursor(85, 100);          //Overwrite any text that might
  tft.print("                ");  //be in this position before
  tft.setCursor(85, 100);          //writting new text
  tft.print("22.3");

  //Print out the temperature
  tft.setTextSize(4);
  tft.setCursor(85, 180);          //Overwrite any text that might
  tft.print("                ");  //be in this position before
  tft.setCursor(85, 180);          //writting new text
  tft.print("53.8%");
}

void loop() {
  //Add your own code here
}




// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint16_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print("File not found");
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print("File size: "); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print("Header size: "); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print("Bit Depth: "); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print("Image size: ");
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r,g,b));
          } // end pixel
        } // end scanline
        Serial.print("Loaded in ");
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File & f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File & f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
