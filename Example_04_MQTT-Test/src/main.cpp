#include <Arduino.h>

/*
 Name:	MQTT-Test	
 Created:	4/29/2020 
 Author:	H. Jachs
 Counts button strokes and reports via MQTT
*/



#include <ESP8266WiFi.h>  // WiFi Bibliothek
#include <PubSubClient.h> // MQTT Bibliothek

//#define WIFI_AP "devices"
//#define WIFI_PASSWORD "Z6Opm2ezigp8"

#define WIFI_AP "PBS-48A309"
#define WIFI_PASSWORD "wimmer-hoehe-10"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

#define BUTTON_PIN 0     // button pin GPIO0, D3 (Flash-Button)
int buttonState;             // variable for reading the pushbutton status
int debounce = 0;

int counter;
char buf[50];

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to AP, IP address:");
  Serial.println(WiFi.localIP());
}

void reconnect() {
	// Solange wiederholen bis Verbindung wiederhergestellt ist
	while (!client.connected()) {
		Serial.print("Versuch des MQTT Verbindungsaufbaus...");

		//Verbindungsversuch:
		if (client.connect("arduinoClient")) {
			Serial.print(counter);
			Serial.println("Erfolgreich verbunden!");
			// versenden einer Nachricht in outTopic 
			client.publish("outTopic", "ESP8266 online!");
		}
		else { // Im Fehlerfall => Fehlermeldung und neuer Versuch
			Serial.print("Fehler, rc=");
			Serial.print(client.state());
			Serial.println(" Nächster Versuch in 5 Sekunden");
			// 5 Sekunden Pause vor dem nächsten Versuch
			delay(5000);
		}
	}
}

void setup()
{
	Serial.begin(9600);
    Serial.println("ESP-MQTT Client");
	InitWiFi();
	delay(500);     // kleine Pause
	client.setServer("test.mosquitto.org", 1883); // MQTT-Broker
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{ // Solange probieren bis es klappt:
	if (!client.connected()) {
		reconnect();
	}

	buttonState = digitalRead(BUTTON_PIN);
	if (buttonState == LOW) {
		if (debounce == 0) {
			counter++;
			debounce = 1;
            sprintf(buf, "Button pressed, count = %d ", counter);
			Serial.println(buf);
			client.publish("outTopic", buf);
		}
	}
	else {
		debounce = 0;
	}

	client.loop();


}