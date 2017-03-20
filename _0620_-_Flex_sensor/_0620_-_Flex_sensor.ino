/*  0620 - Flex sensor demo
 * 
 * This sketch shows you how to use an analog flex sensor.
 * Connect the sensor to an analog pin. As the sensor is
 * flexed, the reading on the analog pin changes proportional.
 * 
 * This sketch will turn on an LED when the sensor is flexed
 * past a threshold.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a flex sensor 
 *  - 5mm LED
 *  - 250 Ohm resistor for the LED
 *  - 20 kOhm resistor for the flex sensor
 *  
 *  Libraries
 *  ---------
 *  None
 *
 * Connections
 * -----------
 *  
 * Refer to the schematic that is available with this lecture.
 *     
 * 
 *  
 *  Created on March 20 2017 by Peter Dalmaris
 * 
 */

#define led_pin    8  //this is digital pin 8
#define flex_pin   0  //This is analog pin A0

 int flex_sensor_threshold = 700; // When the flex sensor reading is past this value
                                  // the LED will turn on.

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin , OUTPUT);
  pinMode(flex_pin, INPUT);  //Not necessary since analog pins are inputs by default

  Serial.begin(9600);  //We'll use the serial monitor to see the flex sensor values
}

void loop() {
  int flexposition;    // Input value from the analog pin.
  flexposition = analogRead(flex_pin);
  Serial.println(flexposition);

  if (flexposition > flex_sensor_threshold)
  {
    // turn LED on:
    digitalWrite(led_pin, HIGH);
  } else
  {
    // turn LED off:
    digitalWrite(led_pin, LOW);
  }
  delay(100);
}
