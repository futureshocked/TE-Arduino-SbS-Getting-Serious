/*  Membrane 4x4 keypad with the 74C922 key encoder
 * 
 * This sketch shows you how to use the 4x4 membrane 
 * keypad with the 74C922 16-key encoder. When a key is pressed
 * on the keypad, it is shown on a 16x2 LCD display 
 * using the I2C backpack adaptor. 
 * 
 * The encoder chip makes it possible to connect a 16-key keypad
 * to the Arduino using only 3 digital pins for the data and 
 * 1 pin for the interrupt. The encoder, internally, takes care of
 * dedouncing, and pushes the last key pressed at the output.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - An I2C to LCD backpack adaptor
 *  - An 16x2 LCD screen
 *  - A 4x4 membrane keypad
 *  - A 74C922 16-key encoder
 *  - 2 x 0.1 uF capacitors (code 103)
 *  - 1 x 1 uF capacitor (code 101)
 *  - Jumper wires
 *  - Breadboard
 *  
 *  Libraries
 *  ---------
 *  - LCD
 *  - LiquidCrystal_I2C
 *  - Keypad
 *
 * Connections
 * -----------
 *  I2C backpack  |    Arduino Uno
 *  -----------------------------
 *      GND       |      GND
 *      Vcc       |      5V
 *      SDA       |      SDA or A4
 *      SCL       |      SCL or A5
 *      
 *     74C922     |   Arduino Uno 
 *  -----------------------------
 *        17      |        7
 *        16      |        6
 *        15      |        5
 *        14      |        4
 *        12      |        1
 *        
*      74C922     |   Keypad 
 *  -----------------------------        
 *      Col 1     |      11
 *      Col 2     |      7
 *      Col 3     |      8
 *      Col 4     |      10
 *      Row 1     |      1
 *      Row 2     |      2
 *      Row 3     |      3
 *      Row 4     |      4
 *      
 *  Other 74C922 connections    
 *  ---------------------------
 *  C1 0.1 uF between 18 and GND    
 *  C2 0.1 uF between 5 and GND
 *  C3 1 uF between 6 and GND
 *  13 to GND
 *  9 to GND
 *  18 to 5V
 *  
 * 
 * Other information
 * -----------------
 *  For information on the LiquidCrystal library: https://github.com/marcoschwartz/LiquidCrystal_I2C
 *  Datasheet for 74C922: http://www.soemtron.org/downloads/disposals/74c922.pdf
 *  Original project information: http://embedded-lab.com/blog/mm74c922n-based-encoded-matrix-keypad/
 *  
 *  
 *  Created on March 26 2017 by Peter Dalmaris
 * 
 */
/*
  Project: Arduino and MM74C922N interface demo
  Visit  http://embedded-lab.com/blog/?p=8640 for more details.
  
*/
#include <LiquidCrystal_I2C.h>

#define PINA 7
#define PINB 6
#define PINC 5
#define PIND 4

LiquidCrystal_I2C lcd(0x27,16,2);

int output, press_status = 0;
char str[16] = {'1', 'A', '3', '2', '4', 'B', '6', '5', '7', 'C', '9', 
                '8', '*', 'D', '#', '0'};
void setup()
{
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  Serial.println("MM74C22N Demo!");
  attachInterrupt(0, Read_Data, FALLING);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Press a key!");
  lcd.setCursor(0, 1);
  lcd.print("You pressed: ");
}

void loop()
{
  if(press_status){
    lcd.setCursor(12, 1);
    lcd.print(str[output]);
    lcd.print(" ");
    lcd.print(output, HEX);
    press_status = 0;


  }
}

void Read_Data()
{ 
  output = 0;
  output = output | digitalRead(4);
  output = output << 1;
  output = output | digitalRead(5);
  output = output << 1;
  output = output | digitalRead(6);
  output = output << 1;
  output = output | digitalRead(7);
  press_status = 1;
  
}
