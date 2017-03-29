/*  Membrane 4x4 keypad with 1-wire connection
 * 
 * This sketch shows you how to use the 4x4 membrane 
 * keypad with a 1-wire connection. When a key is pressed
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
 *  - 4 x 1 kOhm resistors - use small tolerance for better results, 1% or better
 *  - 3 x 4.7 kOhm resistors - use small tolerance for better results, 1% or better 
 *  - 1 x 0.1 uF capacitor (104 code)
 *  - Jumper wires
 *  - Breadboard
 *  
 *  Libraries
 *  ---------
 *  - LCD
 *  - LiquidCrystal_I2C
 *  - OnewireKeypad 
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
 *  For information on the OnewireKeypad library: https://github.com/AndrewMascolo/OnewireKeypad
 *  
 *  Created on March 25 2017 by Peter Dalmaris
 * 
 */
 
#include <OnewireKeypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

char KEYS[]= {
  '1','2','3','A',
  '4','5','6','B',
  '7','8','9','C',
  '*','0','#','D',
};

OnewireKeypad <Print, 16 > KP2(Serial, KEYS, 4, 4, A0, 4700, 1000, MediumPrec );
// Precision can be ExtremePrec, HighPrec, MediumPrec, LowPrec
void setup ()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Press a key!");
    lcd.setCursor(0, 1);
    lcd.print("You pressed: ");
    KP2.SetKeypadVoltage(5.0);
    KP2.SetHoldTime(500);
  
}

void loop() 
{
  if ( char key = KP2.Getkey() ) {
  lcd.setCursor(12, 1);
  lcd.print(key);
  }
}



