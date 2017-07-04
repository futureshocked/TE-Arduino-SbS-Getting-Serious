/*  1101 - The Ethernet Shield (W5100) DHCP Server with LCD Shield
 * 
 * This sketch shows you how to create a simple chat server
 * using an Arduino Uno and an Ethernet Shield.
 * 
 * The server simply echoes any incomming text to all other 
 * connected clients.
 * 
 * You can use this sketch to have your chat server acquire
 * an IP address from the local DHCP, or you can assign one
 * manually.
 * 
 * The LCD screen on the LCD shield is used to display
 * the IP address that was assigned to the Ethernet shield.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a compatible Ethernet shield (W5100 chipset)
 *  - Access to an Ethernet switch and CAT5 cable
 *  - Adafruit RGB Character LCD Shield
 *  
 *  Libraries
 *  ---------
 *  - SPI (comes with the Arduino IDE)
 *  - Ethernet (comes with the Arduino IDE)
 *  - Wire
 *  - Adafruit_MCP23017
 *  - Adafruit_RGBLCDShield
 *
 * Connections
 * -----------
 *  
 * Attach the Ethernet shield to the Arduino Uno.
 * Using a Cat5 cable, connect the Ethernet shield 
 * to an Ethernet switch that is already a member
 * of your Local Area Network.
 * 
 * Attach the LCD shield on top of the Ethernet shield
 *     
 * Other information
 * -----------------
 * About the Arduino Ethernet shield v2: https://store.arduino.cc/usa/arduino-ethernet-shield-2
 * About the Arduino Ethernet shield v1: https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1
 * The Ethernet library: https://www.arduino.cc/en/Reference/Ethernet
 * For information on the LCD chield: https://www.adafruit.com/product/714
 * For information on the Adafruit_RGBLCDShield library: https://github.com/adafruit/Adafruit_TinyRGBLCDShield
 * For information on the Adafruit_MCP23017 library: https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library  
 * 
 * 
 * Created on July 4 2017 by Peter Dalmaris
 * 
 */
/*
 DHCP Chat  Server
 
 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 Using an Arduino Wiznet Ethernet shield. 
 
 THis version attempts to get an IP address using DHCP
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 21 May 2011
 modified 9 Apr 2012
 by Tom Igoe
 Based on ChatServer example by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192,168,111, 177);
IPAddress gateway(192,168,111, 1);
IPAddress subnet(255, 255,255, 0);

// telnet defaults to port 23
EthernetServer server(23);
boolean gotAMessage = false; // whether or not you got a message from the client yet

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

int col = 0; // We'll use this variable to keep track of the column to where the 
             // next character will be printer.

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // start the Ethernet connection:
  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);     // If you want to manually assign an available IP address
                                                  // to your Arduino, you can use this constructor outside the 
                                                  // "if" statement.
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  lcd.setCursor(0, 0);    // Set the screen cursor to row 0, column 0
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
    lcd.print(ip[thisByte], DEC);
    lcd.print(".");
  }
  Serial.println();
  // start listening for clients
  server.begin();

  lcd.setCursor(0, 1);           // Set the cursor to Col 0, row 1 (second line)
  lcd.print("---------------");  // Print out a line of dashes
  
}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!gotAMessage) {
      Serial.println("We have a new client");
      client.println("Hello, client!"); 
      gotAMessage = true;
    }

    // read the bytes incoming from the client:
    char thisChar = client.read();
    // echo the bytes back to the client:
    server.write(thisChar);
    // echo the bytes to the server as well:
    Serial.print(thisChar);

    lcd.setCursor(col, 1); // Set the screen cursor to row 1 (second row), column 0
    lcd.print(thisChar);   // Print this character to the LCD screen.
    col++;                 // Increament col by 1 for the next character
    if (col==15)
    {   
        lcd.setCursor(0, 1);           // Set the cursor to Col 0, row 1 (second line)
        lcd.print("---------------");  // Print out a line of dashes
        col=0;                         // Reset the counter for the second row
    }
  }
}

