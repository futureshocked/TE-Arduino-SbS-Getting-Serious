/*  1120 - The Ethernet Shield (W5100) simple GET request parser
 * 
 * This sketch shows you how to create a simple that contains a GET request
 * parser. You can use this parser to turn LEDs on and off.
 * 
 * The sketch also creates a simple web form that displays buttons in the
 * client's web browser.
 * 
 * This sketch includes two variations of the parser. 
 * The first one is simple, and can only parse a single value pair in the GET request.
 * 
 * The second one is a slightly more involved and can parse multiple value pairs.
 * 
 * Experiment with both to understand how they work so that you can extend them.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a compatible Ethernet shield (W5100 chipset)
 *  - Access to an Ethernet switch and CAT5 cable
 *  - One LED
 *  - A 330 Ohm resistor for the LED
 *  - A breadboard
 *  - Jumper wires
 *  
 *  Libraries
 *  ---------
 *  - SPI (comes with the Arduino IDE)
 *  - Ethernet (comes with the Arduino IDE)
 *
 * Connections
 * -----------
 *  
 * Attach the Ethernet shield to the Arduino Uno.
 * Using a Cat5 cable, connect the Ethernet shield 
 * to an Ethernet switch that is already a member
 * of your Local Area Network.
 * 
 * Attach the LED to the resistor. Attach the LED anode to digital pin 8.
 * Attach the other pin of the resistor to GND.
 *     
 * Other information
 * -----------------
 * About the Arduino Ethernet shield v2: https://store.arduino.cc/usa/arduino-ethernet-shield-2
 * About the Arduino Ethernet shield v1: https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1
 * The Ethernet library: https://www.arduino.cc/en/Reference/Ethernet
 *  
 *  Created on July 4 2017 by Peter Dalmaris
 * 
 */

#include <SPI.h>
#include <Ethernet.h>

byte           mac[]        = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte           ip[]         = { 192,168,111,177 };
String         message      = "";     //Will hold the confirmation message that will be shown to the user
EthernetServer server(80);
String         get_request  = "";     //Holds the GET request

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("ready");
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for new clients
  EthernetClient   client = server.available();
  String return_message; 
  if (client) {
    Serial.println("new client");
    boolean sentContent    = false;
    get_request           = "";
    boolean        currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char       c = client.read();
        if(c == '\n')             // Because we are only processing a GET request, we are only interested in the 
                                  // content of the first line. So, as soon as we have the first line of the request
                                  // (which always ends with \n, we can ignore the rest and go ahead to parse the request.
        { 
          return_message = parseGetRequest(get_request);
          break;
        }

        get_request += c;  // Store this character from the client in the get_request string.

      }
    }
    
    if (!sentContent){
       construct_page(client, return_message);         
       sentContent = true;        
     }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void construct_page(EthernetClient &client, String &rmessage)
{
    print_header(client);
    print_form(client);
    print_confirmation(rmessage, client);
    end_page(client);
}

void print_header(EthernetClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print("<html><head><title>");   
    client.print("GET request example");
    client.println("</title><body>");
}
      
void print_confirmation(String &confirmation_message, EthernetClient &client)
{
  client.print("Action performed: <b>");
  client.print(confirmation_message);
  client.print("</b>");
}

void print_form(EthernetClient &client)
{
  client.println("<h2>Click buttons to turn pin 8 on or off</h2>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led08'");
  client.println(" value='0'><input type='submit' value='Off'/></form>");
  client.print("<form action='/' method='GET'><p><input type='hidden' name='led08'");
  client.print(" value='1'><input type='submit' value='On'/></form>");
}
    
void end_page(EthernetClient &client)
{     
    client.print("</body>");
    client.print("</html>");
}

String parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);
  boolean searching = true;
  int current_index = 0;
  String return_message = "";
  while(searching==true)
  {
  int   led_index    = str.indexOf("led", current_index);
  int   equal_index  = str.indexOf("=", current_index);
  int   led_pin      = str.substring(led_index+3,equal_index).toInt();      // Find the substring that contains the pin number,
                                                                            // and convert it into an int    
  // ** Single value pair parsing **
  // Use the following line if you plan to only have a single value pair                                                                            
//  int   led_val      = str.substring(equal_index+1,str.length()).toInt(); // Find the substring that contains the value,
                                                                            // and convert it into an int  

  // ** Multiple value pair parsing **                                                                          
  // If we have multiple value pairs, we need to find out the next "led" string so that we can
  // go back and extract the value for the current led.
  // If there is no next "led" then look for end of line.
  int   led_val = 0;
  if (str.indexOf("led", equal_index)>0) // If the "led" string can't be found in the str, the index is -1
  {                                                                                    
     led_val      = str.substring(equal_index+1,str.indexOf("led", equal_index)-1).toInt();
  } else
  {
    led_val      = str.substring(equal_index+1,str.length()).toInt();
      searching = false;
  }
  current_index = equal_index + 1;
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
  }
  return return_message;
}

void executeInstruction(int pin, int val)
{  
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    //analogWrite(pin, val);   //If the pin is PWM-capable, you can use analogWrite
}

