/*  2348 - Helium Simple Environment Logging with remote configuration
 * 
 * This sketch show how to use the Helium infrastructure to report values
 * from a DHT22 and a BMP180 sensor, and also distribute simple configuration
 * values from the Helium console to an Atom.
 * 
 * To use this skletch you will need the components listed below.
 * 
 * You will also need a Helium Dashboard account. You can transmit data from 
 * the sensors to the any available Channel in your Helium account. 
 * 
 * You can create any available type of channel in the Helium Dashboard, but I
 * recommend you start with a HTTP channel, which you can configure to forward
 * the data a temporary RequestBin URL. You can use the same setup to forward 
 * the data to your own web application or other IoT tool.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - BMP180
 *  - DHT22
 *  - Helium Element
 *  - Helium Atom
 *  - LED
 *  - 330 Ω resistor for the LED
 *  - 10 kΩ pull-up resistor for the DHT22
 *  
 *  Libraries
 *  ---------
 *  - Adafruit_Sensor
 *  - Adafruit_BME280
 *  - Helium
 *  - HeliumUtil
 *  - Wire
 *  - Adafruit_BMP085
 *  - DHT
 *
 * Connections
 * -----------
 *  To use the I2C interface:
 *  
 *  Arduino Uno   |     BMP180
 *  ------------------------------
 *        5V      |       Vin
 *        GND     |       GND
 *     SCL or A5  |       SCK 
 *     SDA or A4  |       SDI
 *     
 * 
 *  Arduino Uno   |     DHT22
 *  ------------------------------
 *        5V      |       Pin 1
 *        2       |       Pin 2
 *        -       |       Pin 3 
 *        GND     |       Pin 4
 * 
 * If you wish, connect an LED to pin 9 in order to  
 * get visible transmission notifications.
 *        
 *  It is possible to use any other digital pins in 
 *  order to implement the SPI interface.
 *  
 *  Created on December 18 2017 by Peter Dalmaris
 * 
 */

#include "Arduino.h"
#include "Board.h"
#include "Helium.h"
#include "HeliumUtil.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define DHTPIN 2         // the data pin for the DHT22
#define DHTTYPE DHT22    // the type of the DHT sensor

#define activity_LED 9   // This LED will light up when data is being transmitted to Helium

int32_t send_interval = 5000;  // This is the default data send interval. This can be changed over
                               // the air via Helium configuration variables.
int32_t location_id = 1;       // This is an id for the Helium Atom. It helps me identify where a 
                               // particular record originated from. Each Atom can be given its own
                               // ID. Great in case you have lots of Atoms in your network.

//#define CHANNEL_NAME "HTTP_helium_test"
#define CHANNEL_NAME "Heroku_Web_app_csv"             // This is the name of the channels that forwards data
                                                  // to my custom web app on Heroku. If you are simply 
                                                  // testing out Helium, you can replace this with a 
                                                  // Channel name that forwards the data to a requestbin (requestb.in)
#define CONFIG_INTERVAL_KEY "config.interval_ms"  // This is the name of the interval configuration variable. Simply take
                                                  // the variable you created in the Dashboard for your Atom and prepend "config."
                                                  // to it.
#define CONFIG_LOCATION_KEY "config.location"     // Another configuration variable

Helium  helium(&atom_serial);                     // Create the helium object that will allow us to interact with the Atom 
                                                  // device. We will be using the software serial port for the Arduino-Atom
                                                  // communication.
Channel channel(&helium);                         // Setup the object that will represent the Helium channel to which the data from 
                                                  // this Atom is sent.  
Config  config(&channel);                         // Setup the object that will make it possible to update configuration variables 
                                                  // over the air. In this examples, we will do this with send_interval and location_id.


DHT dht(DHTPIN, DHTTYPE);        // Setup the object for the DHT sensor.
Adafruit_BMP085 bmp;             // Setup the object for the BMP sensor.


// This method is used to get updated configuration values from the Helium network. You can configure t these variables through
// your Helium Dashboard.
// It will also report updated values back to the network
void update_config(bool stale)
{
    if (stale)
    {
        Serial.println(F("Fetching Config - "));
        int status = config.get(CONFIG_INTERVAL_KEY, &send_interval, 5000);  //Update the interval_ms variable. If the update fails,
                                                                             //use the value 5000 as default.
        report_status(status);                                               //Print out a message that conveys the status of the Atom.

        status = config.get(CONFIG_LOCATION_KEY, &location_id, 1);           //Update the location_id variable. If the update fails,
                                                                             //use the value 1 as default.
        report_status(status);                                               //Print out a message that conveys the status of the Atom.

        if (status == helium_status_OK)                                      //If the variables were updated succesfully...
        {
            Serial.println(F("Updating Config - "));
            status = config.set(CONFIG_INTERVAL_KEY, send_interval);         // Report the new interval_ms configuration back to the Helium network.
            report_status(status);
            status = config.set(CONFIG_LOCATION_KEY, location_id);           // Report the new location_id configuration back to the Helium network.
            report_status(status);
        }
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println(F("Starting"));

    helium.begin(HELIUM_BAUD_RATE);                   // Start Helium-Arduino communication
    helium_connect(&helium);                          // Connect the Atom to the Helium Network
    channel_create(&channel, CHANNEL_NAME);           // Connect to the channel that will receive our data
    update_config(true);                              // Update the configuration variables from the network

    dht.begin();                                      // Start the DHT sensor

    if (!bmp.begin()) {                               // Start the BMP sensor
    Serial.println(F("Could not find a valid BMP085 sensor, check wiring!"));
    while (1) {}
    }

    pinMode(activity_LED, OUTPUT);                    
    digitalWrite(activity_LED, LOW);                  // Turn off the activity LED
}



void loop()
{ 

  digitalWrite(activity_LED, HIGH);                   // Turn on the activity LED for the duration of sensor reading
                                                      // and communication with the Helium network.
   
  float h = dht.readHumidity();                       // Read the humidity value.
  float t = dht.readTemperature();                    // Read the temperature value in Celsius.
                                                      // Use dht.readTemperature(true) to read in Fahrenheit.

  if (isnan(h) || isnan(t)) {                         // If the DHT readings fail, write error values in the variables.
    Serial.println(F("Failed to read from DHT sensor!"));
    h = 999;
    t = 999;
  }

  float pressure = bmp.readPressure();               // Read the atmospheric pressure value.

    // There are a few ways to construct the payload string. A simple one (but memory intensive) is to 
    // use the String object, and contatenate its components. 
    // Another way is to use the sprintf function, which has a smaller memory footprint (and is the prefered method).
    // The payload can be anything you like. Typically, JSON and CSV formats are used. 

    // In the example below, we are constructing a JSON payload using String.
//   Construct a small JSON payload.
//   Using String seems to be causing stability problems, perhaps because Stirng is RAM-intensive.
//   Use with care.
//    String data = "{'t':";
//    data = data + t;
//    data = data + ",'h':";
//    data = data + h;    
//    data = data + ",'p':";
//    char pressure_str[5];
//    dtostrf(pressure, 5, 0, pressure_str);
//    data = data + pressure;
//    data = data + ",'l':";
//    data = data + location_id;
//    data = data + "}";

   // In the example below, we use sprintf to construct a CSV payload.
   // Because this function can only process char arrays, we use the dtostrf function to convert floats into char arrays.
   char t_result[6];               // Buffer big enough for 5-character float plus the array end character
   dtostrf(t, 5, 2, t_result);     // Learn more about dtostrf: txplo.re/dtostrf
                                   // This function will convert the float stored in "t" to a char array stored in "t_results".

   char h_result[6];               // As above, but for the humidity.
   dtostrf(h, 5, 2, h_result);
    
   char p_result[5];               // As above, but for the pressure.
   dtostrf(pressure, 5, 0, p_result);

   char payload_message[20];       // Prepare the char array in which the sprintf function will construct the message.
                                   // Be careful to allow enough space in the array to hold the full message. But not too
                                   // much as RAM on the Arduino Uno is limited.
                                   // If you allocated too much RAM, your Arduino may crush without any warning or indication of the cause.   

   sprintf(payload_message, "%s,%s,%s,%i", t_result, h_result,p_result,location_id);  // Construct the payload and store it in payload_message
                                                                                      // Learn more about sprintf: txplo.re/sprintf
                                                                                      // Learn more about printf: txplo.re/printf

//    char buffer[data.length()];               // Uncommend these two lines if you used the String method from above.
//    data.toCharArray(buffer,data.length()+1); //Adding "1" to the string length to avoid trancating the last character.
   Serial.print(F("Sending - "));
   Serial.println(payload_message);
//    Serial.print(buffer);                     // Uncommend this line if you used the String method from above.

//    channel_send(&channel, CHANNEL_NAME, buffer, strlen(buffer));  // Uncommend this line if you used the String method from above.

   channel_send(&channel, CHANNEL_NAME, payload_message, strlen(payload_message));   // Transmit the data to the Helium channel.

    // Wait a while till the next time
   digitalWrite(activity_LED, LOW);            // Turn off the activity LED for the duration of sensor reading
                                                // and communication with the Helium network.

   Serial.print(F("Waiting for next transmission in "));

   update_config(config.is_stale());          // Update the configuration variables if they have been changed in the Helium dashboard
    
   Serial.print(send_interval);
   Serial.println(F("ms .   "));
   delay(send_interval);                      // Wait for the next transmission.
}

