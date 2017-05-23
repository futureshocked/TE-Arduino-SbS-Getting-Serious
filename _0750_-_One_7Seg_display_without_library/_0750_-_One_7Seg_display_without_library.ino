/*  0750 - Single seven segment display directly by the Arduino
 * 
 * This sketch shows you how to drive a single common cathode seven segment 
 * display using only the Arduino's digital pins.
 * 
 * The sketch displays numbers from 0 to 9, plus the dot point.
 * 
 * This sketch was written by Peter Dalmaris for Arduino Step by Step.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - Common cathode seven segment display
 *  - 8 x 330 Ohm resistor for the 8 LED segments
 *  - Breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - None
 *
 * Connections
 * -----------
 *  Arduino Uno and seven segment display:
 *  
 *  Arduino Uno   |   Seven Seg
 *  ------------------------------
 *        GND     |  Common cathode
 *        2       |       A
 *        3       |       B
 *        4       |       C 
 *        5       |       D
 *        6       |       E
 *        7       |       F 
 *        8       |       G    
 *        9       |       Dp
 *     
 *  
 *  
 *  Created on May 13 2017 by Peter Dalmaris
 * 
 */
const byte CHAR_COUNT = 11;
const byte symbols[CHAR_COUNT] = {
//.GFEDCBA
 B00111111, // 0
 B00000110, // 1
 B01011011, // 2 
 B01001111, // 3
 B01100110, // 4 
 B01101101, // 5
 B01111101, // 6 
 B00000111, // 7
 B01111111, // 8 
 B01101111, // 9
 B10000000, // .
};

byte segmentPins[] = {2,3,4,5,6,7,8,9};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(segmentPins[0], OUTPUT);
  pinMode(segmentPins[1], OUTPUT);
  pinMode(segmentPins[2], OUTPUT);
  pinMode(segmentPins[3], OUTPUT);
  pinMode(segmentPins[4], OUTPUT);
  pinMode(segmentPins[5], OUTPUT);
  pinMode(segmentPins[6], OUTPUT);
  pinMode(segmentPins[7], OUTPUT);
  
//  writeLeds(symbols[2]);    //Use this line to test a bit pattern
}

void loop() {

  for (int i = 0; i<CHAR_COUNT; i++)
  {
    writeLeds(symbols[i]);  
    delay(1000);
  }

}

void writeLeds(byte pattern)
{
  for (int i = 0; i<8; i++)
    digitalWrite(segmentPins[i],bitRead(pattern,i)); //bitRead is documented at https://www.arduino.cc/en/Reference/BitRead
}

