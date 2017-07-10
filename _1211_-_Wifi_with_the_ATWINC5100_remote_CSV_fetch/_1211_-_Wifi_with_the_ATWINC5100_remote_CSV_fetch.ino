/*  1211 - The ATWIN1500 wifi breakout simple GET request for a CSV file
 * 
 * This sketch shows you how to fetch a simple CSV file that contains instructions
 * for controlling LEDs. The file can be stored on any web server. The sketch will
 * fetch the data periodically and update the status of the LEDs.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - An Atmel ATWIN1500 Wifi breakout or shield
 *  - Two LEDs
 *  - Two 330 Ohm resistors for the LEDs
 *  - A breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SPI (comes with the Arduino IDE)
 *  - WiFi101 (comes with the Arduino IDE)
 *
 * Connections
 * -----------
 *  
 * Connect the breakout to the Arduino 
 * 
 * Arduino    |   ATWIN1500 breakout
 * ---------------------------------
 *     5V .   | .      Vin
 *     GND .  | .      GND
 *     13 .   | .      SCK
 *     12 .   | .      MISO
 *     11 .   | .      MOSI
 *     8 .    | .      CS
 *     5V .   | .      EN
 *     2 .    | .      IRQ
 *     4 .    | .      RST
 *     
 * Connect the anode of each LED to pins 5 and 6.
 * Connect the cathode of each LED to the current limiting resistor.
 * Connect the other pin of the resistors to Arduino GND.
 * 
 * 
 * to an Ethernet switch that is already a member
 * of your Local Area Network.
 * 
 * Attach the LED to the resistor. Attach the LED anode to digital pin 8.
 * Attach the other pin of the resistor to GND.
 *     
 * Other information
 * -----------------
 * About the ATWIN1500: http://www.microchip.com/wwwproducts/en/ATwinc1500
 * About the Adafruit ATWINC1500 WiFi Breakout: https://www.adafruit.com/product/2999
 * The WiFi101 library: https://www.arduino.cc/en/Reference/WiFi101
 *  
 *  Created on July 8 2017 by Peter Dalmaris
 *  
 * 
 */

#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "ardwifi"; //  your network SSID (name)
char pass[] = "ardwifi987";    // your network password (use for WPA, or use as key for WEP)

String         csv_content  = "";     //Holds the csv string

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "txplore.web.s3-website-us-east-1.amazonaws.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

boolean         reading             = false;  //TRUE while the GET request is being received
int             connectionInterval  = 20000;  //Update every 20 seconds
unsigned long   previousMillis      = 0;
boolean         process_response    = false;  //TRUE will trigger the parser after a response from the server has been received.

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.setPins(8,2,4);   //Pins are CS, IRQ, RST
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  
}

void loop() {
  unsigned long currentMillis = millis();
  //Periodically, contact the server to get the latest values

  if(currentMillis - previousMillis >= connectionInterval)
  {
      previousMillis = currentMillis;
      Serial.println("\nStarting connection to server...");
      // if you get a connection, report back via serial:
      if (client.connect(server, 80)) {
        Serial.println("connected to server");
        // Make a HTTP request:        
        client.println("GET /sample_csv_file_wifi.csv HTTP/1.1");
        client.println("Host: txplore.web.s3-website-us-east-1.amazonaws.com");
        client.println("Connection: close");
        client.println();
      }

      process_response = true;
      reading = false;
      csv_content = "";
  }
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  int store_chars = 0; //We'll use this var to indicate when we should start storing the csv text.
  char last_character = " ";
  boolean currentLineIsBlank = true;
  while (client.available()) {
    char c = client.read();
//        Serial.print(c);
//        Serial.print("reading, csv_content, currentLineIsBlank, c=");
//        Serial.print(reading);
//        Serial.print(", ");
//        Serial.print(csv_content);
//        Serial.print(", ");
//        Serial.print(currentLineIsBlank);
//        Serial.print(", ");
//        Serial.println(c, HEX);
       if(reading && c == '\n') 
        { //reading = false;  
          Serial.println(csv_content);
          parseGetRequest(csv_content);
          csv_content = "";
        }        

        if(reading && c != 10){ 
//          Serial.print("Adding character:");
//          Serial.println(c,HEX);
            csv_content += c;
         }      
    
       if (c == '\n' && currentLineIsBlank)  {
        reading = true; // Found the body of the server response, start reading
        Serial.println("start reading");
       }
       if (c == '\n') {
          currentLineIsBlank = true;
       } 
       else if (c != '\r') {
          currentLineIsBlank = false;
       }
  }
  
  // if the server's disconnected, stop the client:
  if (!client.connected() && process_response == true ) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    process_response = false;
    reading = false;
    // do nothing forevermore:
//    while (true);
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
void parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);
  
  int   led_pin      = str.substring(0,2).toInt();      // Find the substring that contains the pin number,
                                                        // and convert it into an int    
  Serial.print("LED pin: ");
  Serial.println(led_pin);                                                           
  int   led_val      = str.substring(3,6).toInt(); // Find the substring that contains the value,
  Serial.print("Value for pin: ");
  Serial.println(led_val);             
                                                
  executeInstruction(led_pin, led_val);
}

void executeInstruction(int pin, int val)
{  
//    Serial.println("Executing instruction");
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    //analogWrite(pin, val);   //If the pin is PWM-capable, you can use analogWrite
}





