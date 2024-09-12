/*
  TLS WiFi Web client

  Board CA Root certificate bundle is embedded inside WiFi firmware:
  https://github.com/arduino/uno-r4-wifi-usb-bridge/blob/main/certificates/cacrt_all.pem

  Find the full UNO R4 WiFi Network documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples#wi-fi-web-client-ssl
*/

#include "WiFiS3.h"
#include "WiFiSSLClient.h"
#include "IPAddress.h"

#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password (use for WPA, or use as key for WEP)

String csv_content = "";  //Holds the csv string

int status = WL_IDLE_STATUS;

char server[] = "txplore-downloads.s3.amazonaws.com";  // name address for the remote URL (using DNS)

// Initialize the Ethernet client library
// with the IP address or domain and port of the server
// that you want to connect to (port 80 is default for HTTP, 443 is for HTTPS):
WiFiSSLClient client;

boolean reading = false;         //TRUE while the GET request is being received
int connectionInterval = 10000;  //Update every 10 seconds
unsigned long previousMillis = 0;
boolean process_response = false;  //TRUE will trigger the parser after a response from the server has been received.


/* -------------------------------------------------------------------------- */
void setup() {
  /* -------------------------------------------------------------------------- */
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  printWifiStatus();
}


void loop() {
  unsigned long currentMillis = millis();
  //Periodically, contact the server to get the latest values

  if (currentMillis - previousMillis >= connectionInterval) {
    previousMillis = currentMillis;
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 443)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.println("GET /sample_csv_file_wifi.csv HTTP/1.1");
      client.println("Host: txplore-downloads.s3.amazonaws.com");
      client.println("Connection: close");
      client.println();
    }

    process_response = true;
    reading = false;
    csv_content = "";
  }

  // if there are incoming bytes available
  // from the server, read them and print them:
  int store_chars = 0;  //We'll use this var to indicate when we should start storing the csv text.
  char last_character = ' ';
  boolean currentLineIsBlank = true;
  while (client.available()) {
    char c = client.read();
            Serial.print(c);
    //        Serial.print("reading, csv_content, currentLineIsBlank, c=");
    //        Serial.print(reading);
    //        Serial.print(", ");
    //        Serial.print(csv_content);
    //        Serial.print(", ");
    //        Serial.print(currentLineIsBlank);
    //        Serial.print(", ");
    //        Serial.println(c, HEX);
    if (reading && c == '\n') {      
      Serial.println(csv_content);
      parseGetRequest(csv_content);
      csv_content = "";
    }

    if (reading && c != 10) {
      csv_content += c;
    }

    if (c == '\n' && currentLineIsBlank) {
      reading = true;  // Found the body of the server response, start reading
      Serial.println("start reading");
    }
    if (c == '\n') {
      currentLineIsBlank = true;
    } else if (c != '\r') {
      currentLineIsBlank = false;
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected() && process_response == true) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    process_response = false;
    reading = false;

  }
}

/* -------------------------------------------------------------------------- */
void printWifiStatus() {
  /* -------------------------------------------------------------------------- */
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

void parseGetRequest(String &str) {
  Serial.print(" Parsing this string:");
  Serial.println(str);

  int led_pin = str.substring(0, 2).toInt();  // Find the substring that contains the pin number,
                                              // and convert it into an int
  Serial.print("LED pin: ");
  Serial.println(led_pin);
  int led_val = str.substring(3, 6).toInt();  // Find the substring that contains the value,
  Serial.print("Value for pin: ");
  Serial.println(led_val);

  executeInstruction(led_pin, led_val);
}

void executeInstruction(int pin, int val) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, val);
  //analogWrite(pin, val);   //If the pin is PWM-capable, you can use analogWrite
}
