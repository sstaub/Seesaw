#include "Arduino.h"
#include "Seesaw.h"

SeesawNeoKey4 key4(0x30);

bool key1Last;
bool key2Last;
bool key3Last;
bool key4Last;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	delay(2000);
	key4.begin();
	key4.pixel(1, 32, 0, 0);
	key4.pixel(2, 0, 32, 0);
	key4.pixel(3, 0, 0, 32);
	key4.pixel(4, 32, 32, 0);
	}

void loop() {
	if (key4.button(1) != key1Last) {
		if (key1Last == false) {
			key1Last = true;
			Serial.printf("Key 1: Button pressed!\n");
			}
		else {
			key1Last = false;
			}
		}
	if (key4.button(2) != key2Last) {
		if (key2Last == false) {
			key2Last = true;
			Serial.printf("Key 2: Button pressed!\n");
			}
		else {
			key2Last = false;
			}
		}
	if (key4.button(3) != key3Last) {
		if (key3Last == false) {
			key3Last = true;
			Serial.printf("Key 3: Button pressed!\n");
			}
		else {
			key3Last = false;
			}
		}
	if (key4.button(4) != key4Last) {
		if (key4Last == false) {
			key4Last = true;
			Serial.printf("Key 4: Button pressed!\n");
			}
		else {
			key4Last = false;
			}
		}
	}