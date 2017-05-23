/*  0754 - Single seven segment display driven by a 595 shift register IC
 * 
 * This sketch shows you how to drive a single common cathode seven segment 
 * display using a 74HC595 shift register.
 * 
 * The sketch displays numbers from 0 to 9, plus the dot point.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Common cathode seven segment display
 *  - 74HC595 shift register IC
 *  - 330 Ohm resistor for the common cathode
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *  Arduino Uno and 74HC959:
 *  
 *  Arduino Uno   |     74HC959
 *  ------------------------------
 *        5V      |       16
 *        GND     |       8
 *        8       |       14 
 *        9       |       12
 *        10      |       11
 *     
 * 74HC959 and seven segment display:
 * 
 *      74HC959   |     Seven seg
 *  ------------------------------
 *        1       |       A
 *        2       |       B
 *        3       |       C 
 *        4       |       D
 *        5       |       E
 *        6       |       F 
 *        7       |       G    
 *        15      |       Dp
 * 
 *  Connect the display common cathode to GND.
 *  
 *  Created on May 13 2017 by Peter Dalmaris
 * 
 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 9;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 10;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 8;

const byte CHAR_COUNT = 11;
const byte symbols[CHAR_COUNT] = {
//GFEDCBAd
 B01101100, // | |
 B00001100, // 1
 B10110110, // 2 
 B10011110, // 3
 B11001100, // 4 
 B11011010, // 5
 B11111010, // 6 
 B00001110, // 7
 B11111110, // 8 
 B11011110, // 9
 B00000001  // .
};



void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  writeLeds(symbols[0]);  //Use this line to test a bit pattern
}

void loop() {
//  pattern1();
}

void pattern1()
{
  int i=0;
  while(i<CHAR_COUNT)
  {
    writeLeds(symbols[i]);
    i = i+1;    
    delay(500);  
  }
}

void writeLeds(byte pattern)
{
  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
  }


