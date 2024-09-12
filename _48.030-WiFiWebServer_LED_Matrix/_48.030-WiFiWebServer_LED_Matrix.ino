/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe


  Find the full UNO R4 WiFi Network documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples#wi-fi-web-server
 */

#include "WiFiS3.h"
#include "Arduino_LED_Matrix.h"

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

String         get_request  = "";     //Holds the GET request

ArduinoLEDMatrix matrix;

const uint32_t box[] = {
		0x3fc3f,
		0xc30c30c3,
		0xfc3fc000,
};

const uint32_t diagonal[] = {
		0x3fc30428,
		0x42442242,
		0x1420c3fc,
};

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  matrix.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
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
  printWifiStatus();
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
          
          return_message = parseGetRequest(get_request);          
          construct_page(client, return_message);

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


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
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
  
  int   frame_index    = str.indexOf("frame");
  int   equal_index  = str.indexOf("=");
  int   frame_number      = str.substring(frame_index+5,equal_index).toInt(); // Find the substring that contains the frame number,
                                                                              // and convert it into an int                                                                       
  
  //Show the substring indexes and values for debugging
  Serial.print("frame_index, equal_index, frame_pin, frame_val, searching: ");
  Serial.print(frame_index);
  Serial.print(", ");
  Serial.print(equal_index);
  Serial.print(", ");
  Serial.print(frame_number);
  Serial.print(", ");
  Serial.println(searching);
  
  return_message        = "Setting frame ";
  return_message        += frame_number;
  return_message        += "\n";
  executeInstruction(frame_number);
  
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
      client.println(F("<h2>Click buttons to show frame 1 and 2</h2>"));
      client.println(F("<table><tr><th>1</th><th>2</th></tr><tr><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='frame1'"));
      client.print(F(" value='1'><input type='submit' value='Show frame 1'/></form>"));
      client.println(F("</td><td>"));
      client.print(F("<form action='/' method='GET'><p><input type='hidden' name='frame2'"));
      client.print(F(" value='2'><input type='submit' value='Show frame 2'/></form>"));
      client.println(F("</td></tr><tr><td>"));
      // client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led13'"));
      // client.println(F(" value='0'><input type='submit' value='Turn Off pin 13'/></form>"));
      // client.println(F("</td><td>"));
      // client.print(F("<form action='/' method='GET'><p><input type='hidden' name='led06'"));
      // client.println(F(" value='0'><input type='submit' value='Turn Off pin 6'/></form>"));
      client.println(F("</td></tr></table>"));
        
}
    
void end_page(WiFiClient &client)
{     
    client.print(F("</body>"));
    client.print(F("</html>"));
}

void executeInstruction(int frame)
{  
  switch (frame){
    case 1:
      matrix.loadFrame(box);
      break;
    case 2:
      matrix.loadFrame(diagonal);
      break;
  }

  // delay(500);
}

