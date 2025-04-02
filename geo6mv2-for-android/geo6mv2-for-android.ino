#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "ESP8266WiFi.h"

//const char* ssid = "YOUR_SSID";
//const char* password =  "WIFI_PASSWORD";

const char* ssid = "MOVISTAR_D310";
const char* password =  "puPdDU4tXafYmjcpaoGo";

//const char* ssid = "RedmiNet";
//const char* password = "xiaomitron";

// 
WiFiServer wifiServer(1314);

/*
   This sample code demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins (rx) and 3(tx).
 */
static const int RXPin = 0, TXPin = 2;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


// Inicia el Serial, GPS NEO 6M V2 y comunicación como server

void setup() 
{
  // Start serial communication
	Serial.begin(115200);


  // Start communication with NEO6MV2
	ss.begin(GPSBaud);
  WiFi.begin(ssid, password);


  delay(1000);

  Serial.println("\n***Server GPS GEO6MV2***");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Conectando..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
	
}

void loop() {
  WiFiClient client = wifiServer.available();
 
  if (client) 
  {
    Serial.println("Client connected");
    while (client.connected()) 
    {
 
      client.print(neo6mv2data());
      Serial.println(neo6mv2data()); // For DEBUG
	    smartDelay(1000);

	    if (millis() > 5000 && gps.charsProcessed() < 10) {
		  Serial.println(F("No GPS data received: check wiring"));
	  }
  }
  client.stop();
  Serial.println("Client disconnected");
  }

}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms) {
	unsigned long start = millis();
	do {
		while (ss.available()) {
			gps.encode(ss.read());
		}
	} while (millis() - start < ms);
}

