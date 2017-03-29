/*  Membrane 4x4 keypad with 8-wire connection
 * 
 * This sketch shows you how to use the 4x4 membrane 
 * keypad with an 8-wire connection. When a key is pressed
 * on the keypad, it is shown on a 16x2 LCD display 
 * using the I2C backpack adaptor. 
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - An I2C to LCD backpack adaptor
 *  - A 4x4 membrane keypad
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
 * 
 * Other information
 * -----------------
 *  For information on the LiquidCrystal library: https://github.com/marcoschwartz/LiquidCrystal_I2C
 *  For information on the Keypad library: http://playground.arduino.cc/Code/Keypad
 *  
 *  Created on March 25 2017 by Peter Dalmaris
 * 
 */
 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

/*  Use this keyboard layout for the flexible keypad */
//const byte ROWS = 4; //four rows     
//const byte COLS = 4; //four columns  
////define the cymbols on the buttons of the keypads
//char hexaKeys[ROWS][COLS] = {    
//  {'1','2','3','A'},             
//  {'4','5','6','B'},
//  {'7','8','9','C'},
//  {'*','0','#','D'}
//};

//byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
/* ------------------------------ */

/*  Use this keyboard layout for the phonepad */
const byte ROWS = 4; //four rows 
const byte COLS = 3; //four columns

char hexaKeys[ROWS][COLS] = {    
  {'1','2','3'},             
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 2, 3, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad
/* ------------------------------ */

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Press a key!");
    lcd.setCursor(0, 1);
    lcd.print("You pressed: ");
}
void loop()
{
  char customKey = customKeypad.getKey();
  
  if (customKey != NO_KEY){
    lcd.setCursor(12, 1);
    lcd.print(customKey);
  }

}
