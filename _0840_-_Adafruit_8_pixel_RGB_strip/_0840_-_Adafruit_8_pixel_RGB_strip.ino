/*  0840 - Adafruit High Density Neopixel example sketch
 * 
 * This sketch shows you how to manipulate LEDs on an Adafruit High Density Neopixel.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Adafruit High Density Neopixel, with 8 LEDs
 *  
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_NeoPixel.h
 *
 * Connections
 * -----------
 *  
 *  You will need to solder pins or wires to the dedicated pads on the Neopixel board.
 *  
 *  Neopixel    |     Arduino
 *  -------------------------
 *     GND      |      GND
 *     DIN      |      6
 *     5VDC     |      5V
 *     GND      |      GND
 *     
 *  Include a 500 Ohm resistor between DIN on the Neopixel and pin 6 on the Arduino.
 *  Add a 1000 uF capacitor (or close to that value) between the GND and 5V pin on the
 *  Neopixel (observe the polarities!).
 *  
 * 
 * Other information
 * -----------------
 *  Adafruit Neopixels library: https://github.com/adafruit/Adafruit_NeoPixel
 *  How to connect: https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections
 *  
 *  Created on April 4 2017 by Peter Dalmaris
 * 
 */

#include <Adafruit_NeoPixel.h>


#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const uint32_t colors[] = {
      strip.Color(255, 0, 0),       // RED
      strip.Color(0, 255, 0),       // GREEN
      strip.Color(0, 0, 255),       // BLUE
      strip.Color(255, 255, 255),   // WHITE
      strip.Color(128,0,255),       // PURPLE
      strip.Color(0,184,245),       // LIGHT BLUE
      strip.Color(255,255,0),       // YELLOW
      }; 

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
 
}

void loop() {
 //Make all pixels light up with a different color
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, colors[i]);
    strip.show();
    delay(100);
  }

  delay(1000);

  //Make all pixels turn off
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    strip.show();
    delay(200);
  }


  delay(1000);
//strip.setPixelColor(1, colors[0]);
//strip.show();


  // Make one RED pixel roll in two directions
  // A.k.a. Cylon eye
  for(int repeats = 0; repeats <5; repeats++)
  {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i-1, 0);
      strip.setPixelColor(i, colors[0]);
      strip.show();
      delay(100);
    }
    for(int i=strip.numPixels()-1; i>-1; i--) {
      strip.setPixelColor(i+1, 0);
      strip.setPixelColor(i, colors[0]);
      strip.show();
      delay(100);
    }
  }

  //Flash all of the LEDs in GREEN 5 times
  for(int repeats = 0; repeats <5; repeats++)
  {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, colors[6]);  // Make the LEDs yellow      
    }
    
    strip.show();
    delay(200);
    
    for(int i=strip.numPixels()-1; i>-1; i--) {
      strip.setPixelColor(i, 0);        // Turn the LEDs off      
    }
    strip.show();
    delay(200);
  }

  //And finish with the two middle LEDs in green
  strip.setPixelColor(3, colors[1]);
  strip.setPixelColor(4, colors[1]);
  strip.show();
  delay(1000);

  //Turn all the LEDs off for the next loop
  for(int i=strip.numPixels()-1; i>-1; i--) {
      strip.setPixelColor(i, 0);        // Turn the LEDs off      
    }
    strip.show();
}

