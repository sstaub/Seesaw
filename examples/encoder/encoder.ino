#include "Arduino.h"
#include "Seesaw.h"

SeesawEncoder enc;

int32_t position;
int32_t positionLast;
bool buttonLast;

void setup() {
	Serial.begin(9600);
	delay(2000);
	enc.begin();
	enc.position(0);
	enc.pixel(0, 32, 0); // green
	}

void loop() {
	position = enc.position();
	if (position != positionLast) {
    Serial.print("Encoder: ");
    Serial.println(position);
		if (position > 0) enc.pixel(32, 0, 0); // red
		if (position < 0) enc.pixel(0, 0, 32); // blue
		if (position == 0) enc.pixel(0, 32, 0); // green
		positionLast = position;
		}
	if (enc.button() != buttonLast) {
		if (buttonLast == false) {
			buttonLast = true;
			Serial.println("Encoder: Button pressed!");
			}
		else {
			buttonLast = false;
			}
		}
	}
