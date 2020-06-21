#include <Arduino.h>

/*
 Name:	Button-Test	
 Created:	4/29/2020 
 Author:	H. Jachs
 Counts and reports button strokes 
*/


#define BUTTON_PIN 0     		// button pin PORTA.0
int buttonState;             	// variable for reading the pushbutton status
int debounce = 0;

int counter;
char buf[50];

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP); 
	Serial.println("ESP8266 Button-Test: press the FLASH-button");
}

// the loop function runs over and over again until power down or reset
void loop() {
	buttonState = digitalRead(BUTTON_PIN);
	if (buttonState == LOW) {
		if (debounce == 0) {
			counter++;
			debounce = 1;
			sprintf(buf, "Button pressed, count = %d ", counter);
			Serial.println(buf);
		}
	}
	else {
		debounce = 0;
	}
  
}
