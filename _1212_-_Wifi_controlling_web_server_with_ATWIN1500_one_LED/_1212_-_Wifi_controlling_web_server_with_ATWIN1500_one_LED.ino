/*  1212 - The ATWIN1500 wifi breakout simple GET request parser ONE LED only
 * 
 * This sketch shows you how to create a simple server that contains a GET request
 * parser. You can use this parser to turn LEDs on and off.
 * 
 * The sketch also creates a simple web form that displays buttons in the
 * client's web browser.
 * 
 * This sketch supports controlling only one LED at a time.
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
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

String         get_request  = "";     //Holds the GET request

int status = WL_IDLE_STATUS;

WiFiServer server(80);

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
  server.begin();
  // you're connected now, so print out the status:
  printWiFiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  String return_message; 
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
     get_request           = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        get_request += c;  // Store this character from the client in the get_request string.
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          Serial.print("Free RAM:");  // See how much RAM is available before parsing and printing out the response.
          Serial.println(freeRam());
          return_message = parseGetRequest(get_request);          
          construct_page(client, return_message);
          Serial.print("Free RAM:");  // See how much RAM is left after parsing and printing out the response.
          Serial.println(freeRam());
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

String parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);
  boolean searching = true;
  
  String return_message = "";
  
  int   led_index    = str.indexOf("led");
  int   equal_index  = str.indexOf("=");
  int   led_pin      = str.substring(led_index+3,equal_index).toInt();      // Find the substring that contains the pin number,
                                                                            // and convert it into an int    
  // ** Single value pair parsing **                                                                          
  int   led_val      = str.substring(equal_index+1,str.indexOf("HTTP")).toInt(); // Find the substring that contains the value,
                                                                            // and convert it into an int                                                                            
  
  //Show the substring indexes and values for debugging
  Serial.print("led_index, equal_index, led_pin, led_val, searching: ");
  Serial.print(led_index);
  Serial.print(", ");
  Serial.print(equal_index);
  Serial.print(", ");
  Serial.print(led_pin);
  Serial.print(", ");
  Serial.print(led_val);
  Serial.print(", ");
  Serial.println(searching);
  
  return_message        = "Setting LED ";
  return_message        += led_pin;
  return_message        += " to ";
  return_message        += led_val;
  return_message        += "\n";
  executeInstruction(led_pin, led_val);
  
  return return_message;
}

void construct_page(WiFiClient &client, String &rmessage)
{
    print_header(client);
    print_form(client);
    print_confirmation(rmessage, client);
    end_page(client);
}

void print_header(WiFiClient &client)
{
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Connection: close"));  // the connection will be closed after completion of the response
    client.println();
    client.print(F("<html><head><title>"));   
    client.print(F("GET request example"));
    client.println(F("</title><body>"));
}
      
void print_confirmation(String &confirmation_message, WiFiClient &client)
{
  client.print(F("Action performed: <b>"));
  client.print(confirmation_message);
  client.print(F("</b>"));
}

void print_form(WiFiClient &client)
{
      client.println(F("<h2>Click buttons to turn pin 5 and 6 on or off</h2>"));
      client.println(F("<table><tr><th>5</th><th>6</th></tr><tr><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led05'"));
      client.print(F(" value='1'><input type='submit' value='Turn On pin 5'/></form>"));
      client.println(F("</td><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led06'"));
      client.print(F(" value='1'><input type='submit' value='Turn On pin 6'/></form>"));
      client.println(F("</td></tr><tr><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led05'"));
      client.println(F(" value='0'><input type='submit' value='Turn Off pin 5'/></form>"));
      client.println(F("</td><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led06'"));
      client.println(F(" value='0'><input type='submit' value='Turn Off pin 6'/></form>"));
      client.println(F("</td></tr></table>"));
        
}
    
void end_page(WiFiClient &client)
{     
    client.print(F("</body>"));
    client.print(F("</html>"));
}

void executeInstruction(int pin, int val)
{  
//    Serial.println("Executing instruction");
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    //analogWrite(pin, val);   //If the pin is PWM-capable, you can use analogWrite
}

//The ATWIN1500 wifi library uses a lot of RAM. Keep an eye on usage by calling this function
int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
