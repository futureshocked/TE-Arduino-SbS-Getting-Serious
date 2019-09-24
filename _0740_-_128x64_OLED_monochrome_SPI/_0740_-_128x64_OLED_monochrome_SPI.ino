/*  128x64 Monochrome OLED breakout
 * 
 * This sketch shows you how to use a generic SPI 128x64 Monochrome OLED breakout
 * with the SH1106 controller using the U8g2lib library.
 * 
 * The sketch simply prints text to the display.
 * 
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - SPI 128x64 Monochrome OLED breakout with the SH1106 
 *  
 *  
 *  Libraries
 *  ---------
 *  - U8g2lib.h
 *  - SPI.h
 *
 * Connections
 * -----------
 *  
 *  SH1106 SPI OLED  |   Arduino Uno 
 *  -------------------------
 *      CLK   |       13
 *      MOSI  |       11
 *      CS    |       10
 *      D/C   |       9
 *      VIN   |       5V
 *      GND   |       GND
 *  
 * 
 * Other information
 * -----------------
 *  For information on the U8g2lib library: https://github.com/olikraus/u8g2  
 *  Setup and reference for the library: https://github.com/olikraus/u8g2/wiki
 *  For available fonts, look here: https://github.com/olikraus/u8g2/tree/master/tools/font/build/single_font_files
 *  Reference programming information for U8g2lib: https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbox
 *  
 *  Created on April 1 (no joke) 2017 by Peter Dalmaris
 * 
 */
/*

  
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <U8g2lib.h>

#include <SPI.h>


//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  // Good for Arduino Uno
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 4, /* reset=*/ 3);

void setup(void) {
  u8g2.begin();

  u8g2.clearBuffer();          // clear the internal memory
  
  // Write some text
  u8g2.setFont(u8g2_font_ncenR08_tf);
  //drawStr(x,y,string)
  u8g2.drawStr(5,15,"Tech Explorations");  // write something to the internal memory
  u8g2.drawStr(5,30,"128x64!");  // write something to the internal memory            

  // Write some lines
  //u8g2.drawLine(x1,y1,x2,y2)
  u8g2.drawLine(0, 0, 0, 63);
  u8g2.drawLine(0, 0, 127, 0);
  u8g2.drawLine(127, 0, 127, 63);
  u8g2.drawLine(0, 63, 127, 63);
  
  u8g2.sendBuffer();      // transfer internal memory to the display
}

void loop(void) {
}

