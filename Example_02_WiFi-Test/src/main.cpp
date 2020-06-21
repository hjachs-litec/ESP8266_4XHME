#include <Arduino.h>

/*
 Name:	Wifi-Test	
 Created:	4/29/2020 
 Author:	Herbert Jachs
 ESP8266 Wifi-Test
 Connects to WLAN and reports assigned IP-Address
*/

#include <ESP8266WiFi.h>

void setup()
{
	Serial.begin(9600);
	Serial.println();

	Serial.print("Connecting to WLAN");

	WiFi.begin("PBS-48A309", "wimmer-hoehe-10");

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();

	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());
}

void loop() {}

