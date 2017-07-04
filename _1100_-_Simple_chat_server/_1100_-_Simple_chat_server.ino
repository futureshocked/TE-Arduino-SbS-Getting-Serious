/*  1100 - The Ethernet Shield (W5100) DHCP Server
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
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - a compatible Ethernet shield (W5100 chipset)
 *  - Access to an Ethernet switch and CAT5 cable
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
 * Other information
 * -----------------
 * About the Arduino Ethernet shield v2: https://store.arduino.cc/usa/arduino-ethernet-shield-2
 * About the Arduino Ethernet shield v1: https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1
 * The Ethernet library: https://www.arduino.cc/en/Reference/Ethernet
 *  
 *  Created on July 4 2017 by Peter Dalmaris
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

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

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
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  // start listening for clients
  server.begin();
 
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
  }
}

