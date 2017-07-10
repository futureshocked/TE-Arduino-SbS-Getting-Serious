/*  1210 - ATWIN1500 Wifi breakout simple reporting web server
 * 
 * This sketch shows you how to create a simple web server
 * using an Arduino Uno and the Adafruit ATWIN1500 Wifi breakout.
 * 
 * The server prints out values acquired from a DHT22 and light sensor.
 * 
 * You can modify this sketch to add other sensors and report their values.
 * 
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - An Atmel ATWIN1500 Wifi breakout or shield
 *  - Adafruit_Sensor (use the Library Manager to install it)
 *  - DHT (use the Library Manager to install it)
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
 * Other information
 * -----------------
 * About the ATWIN1500: http://www.microchip.com/wwwproducts/en/ATwinc1500
 * About the Adafruit ATWINC1500 WiFi Breakout: https://www.adafruit.com/product/2999
 * The WiFi101 library: https://www.arduino.cc/en/Reference/WiFi101
 *  
 *  Created on July 8 2017 by Peter Dalmaris
 * 
 */
#include <SPI.h>
#include <WiFi101.h>
#include <Adafruit_Sensor.h>    //If you are using the Adafruit DHT library, make sure 
                                // that Adafruit_Sensor.h is required first 
#include "DHT.h"

#define DHTPIN 3     // what pin we're connected to

char ssid[] = "ardwifi"; //  your network SSID (name)
char pass[] = "ardwifi987";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial.println("Simple reporting web server");
  dht.begin();

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
  
  server.begin();

  // you're connected now, so print out the status:
  printWiFiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin

          int sensorReading = analogRead(0);
          client.print("analog input ");
          client.print(0);
          client.print(" is ");
          client.print(sensorReading);
          client.println("<br />");       


          float h = dht.readHumidity();
          float t = dht.readTemperature();

          // check if returns are valid, if they are NaN (not a number) then something went wrong!
          if (isnan(t) || isnan(h)) {
            Serial.println("Failed to read from DHT");
          } 
          else {
            client.print("Humidity: ");
            client.print(h);
            client.println("<br />");       
            client.print("Temperature: ");
            client.print(t);
            client.print(" *C");
            client.println("<br />");       
          }

          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
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
