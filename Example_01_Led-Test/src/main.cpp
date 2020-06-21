#include <Arduino.h>

/*
 Name:	blink1	
 Created:	4/29/2020 
 Author:	H. Jachs
 ESP8266 LED-Blink
 Blink the blue LED on the ESP-module
*/


#define LED 16					//OnBoard-LED pin

void setup() {
	pinMode(LED, OUTPUT); 		// LED-pin as output
	Serial.begin(9600);
	Serial.println("Blinking led on ESP8266");
}


void loop() {					// runs forever
	digitalWrite(LED, LOW);   	// LED on (acive low on the ESP)                                 
	Serial.println("Led on");	// control-output
	delay(1000);              	// wait 
	digitalWrite(LED, HIGH);  	// LED off 
	Serial.println("Led off");
	delay(1000);              	// wait 
}
