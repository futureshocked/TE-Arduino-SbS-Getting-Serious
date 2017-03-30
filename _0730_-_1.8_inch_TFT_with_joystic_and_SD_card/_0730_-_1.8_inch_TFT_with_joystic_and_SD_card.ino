/*  Adafruit 1.8" Color TFT Shield w/microSD and Joystick
 * 
 * This sketch shows you how to use the the Adafruit 1.8" color
 * TFT display, with SD card module and joystick interface.
 * 
 * The sketch loads a bitmap image that makes up the user interface.
 * It contains four graphical buttons and one areas where text
 * is printed. The user can select one of the available buttons using
 * the joystick and pressing it. When a selection is made, the button
 * ID is shown on the display.
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
 *  - Adafruit 1.8" TFT Shield with SD card module and joystick
 *  
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_GFX.h
 *  - Adafruit_ST7735.h
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
 *  For information on the Adafruit ST7735 (TFT) library: https://github.com/adafruit/Adafruit-ST7735-Library
 *  
 *  
 *  Created on March 29 2017 by Peter Dalmaris
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
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5


uint8_t selection_box_height = 25; //This is how tall the selection box is
uint8_t spacing = 11;
//Add or subtract this much every time
//the joystick is pushed up or down.
int position = 0; //this stores the position of the selection box

// The following code is for debouncing the joystick and get more accurate readings from it
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 500;    // the debounce time; increase if the output flickers
/////// End of debouncing segment ////////////////

void setup(void) {
  Serial.begin(9600);

  // Initialize 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("OK!");

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
 
  bmpDraw("tft18.bmp", 0, 0);

  //Starting position for the selector box
  tft.drawRect(10, 8, 50, selection_box_height, ST7735_RED);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(1);
  tft.setCursor(70, 10);
  tft.print("Button");
}

void loop() {
  Serial.println(position);
  uint8_t b = readButton();
  tft.setTextSize(3);
  if (b == BUTTON_DOWN) {
    tft.drawRect(10, 8 + (selection_box_height  + spacing + position)* position, 50, selection_box_height, ST7735_WHITE);
    
    if (position < 2)
      position += 1; // Add one to the position of the selection box
    else
      position = 3;
    
    tft.drawRect(10, 8 + (selection_box_height  + spacing+ position)* position, 50, selection_box_height, ST7735_RED);
  }
  if (b == BUTTON_LEFT) {
    //    Do something here

  }
  if (b == BUTTON_UP) {

    tft.drawRect(10, 8 + (selection_box_height  + spacing+ position)* position, 50, selection_box_height, ST7735_WHITE);
    
    if (position > 1)
      position -= 1; // Add one to the position of the selection box
    else
      position = 0;

    tft.drawRect(10, 8 + (selection_box_height  + spacing+ position)* position, 50, selection_box_height, ST7735_RED);


  }
  if (b == BUTTON_RIGHT) {
    //    Do something here

  }
  if ((b == BUTTON_SELECT)) {
    tft.setTextColor(ST7735_RED, ST7735_WHITE );
    tft.setCursor(70, 20);
    tft.setTextSize(3);
    tft.print(position);
    Serial.print("Position: ");
    Serial.print(position);
  }

}

uint8_t readButton(void) {
  float a = analogRead(3);

  a *= 5.0;
  a /= 1024.0;

  if (a < 3.3)
  {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      lastDebounceTime = millis();
      
      Serial.println(a);
      if (a < 0.2) return BUTTON_DOWN;
      if (a < 1.0) return BUTTON_RIGHT;
      if (a < 1.5) return BUTTON_SELECT;
      if (a < 2.0) return BUTTON_UP;
      if (a < 3.2) return BUTTON_LEFT;
      else return BUTTON_NONE;
    } else
      return BUTTON_NONE;
  }
}


#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint8_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if ((x >= tft.width()) || (y >= tft.height())) return;

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
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print("File size: "); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print("Header size: "); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print("Bit Depth: "); Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print("Image size: ");
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
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

        for (row = 0; row < h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col = 0; col < w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r, g, b));
          } // end pixel
        } // end scanline
        Serial.print("Loaded in ");
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
