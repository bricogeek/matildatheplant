/*
 *  Matilda The Plant Thinkspeak log
 *  Oscar Gonzalez - July 2017
 *  www.BricoGeek.com
 *
 *  GitHub Repo: (Feel free to send your pull request with improvements!)
 *  https://github.com/bricogeek/matildatheplant
 * 
 *  Blog post:
 *  http://blog.bricogeek.com/noticias/arduino/matilda-the-plant-planta-conectada-con-esp8266-a-thingspeak/
 * 
 *  Conections:
 *  
 *  DHT11 Pin         ESP8266 (HUZZAH)
 *  1                 3.3V
 *  2                 2
 *  3                 Not connected
 *  4                 GND
 *  
 *  Soil sensor
 *  Connect VCC and GND. Then output pin to de pin2 of the ESP8266 through a 2.2K resistor. Then, a 1K resistor from pin 2 to GND.
 *  
 */

#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11     // DHT 11 

WiFiClient  client;
DHT_Unified dht(DHTPIN, DHTTYPE);

/*  
  ---------------------------------------------------------------------------------------------------
  Configure here
  ---------------------------------------------------------------------------------------------------
*/

// Wifi Settings
const char* ssid     = "YOUR_SSID";
const char* password = "YOURPOWERPASSWORDOFMORDOR";

// ThingSpeak Settings
const int channelID = 0000000; // Your thinkspeak channel ID
String writeAPIKey = "SECRETKEY"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 60 * 1000; // post data every 60 seconds
// ---------------------------------------------------------------------------------------------------

// Matilda Quick and Dirty code ;)

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.begin();  

  // We start by connecting to a WiFi network  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  sensor_t sensor;
  sensors_event_t event;  
  int soilhum = analogRead(A0);   
  int temperature=0;
  int humidity=0;
  long rssi=0;

  // Measure Signal Strength (RSSI) of Wi-Fi connection
  rssi = WiFi.RSSI();  

  Serial.println(soilhum);

  // Get temperature event and print its value.  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    temperature = 0;
    Serial.println("Error reading temperature!");
  }
  else {
    temperature = event.temperature;
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    humidity = 0;
    Serial.println("Error reading humidity!");
  }
  else {
    humidity = event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }

  // Send data to Thingspeak
  if (client.connect(server, 80)) {

    // Construct API request body
    String body = writeAPIKey;
    body +="&field1=";
    body += humidity;
    body +="&field2=";
    body += temperature;
    body +="&field3=";
    body += rssi;
    body +="&field4=";
    body += soilhum;        
    body += "\r\n\r\n";           

    Serial.println(body);
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
  
  }
  client.stop();
    
  // wait and then post again
  delay(postingInterval);
}