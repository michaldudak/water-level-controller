#include <arduino.h>
#include "../include/log.h"

void initializeSerialLogger() {
	Serial.begin(115200);

	int attempts = 10;
	while (!Serial) {
		delay(100);
		if (--attempts == 0) {
			break;
		}
	}
}

void logMessage(const char* message) {
	if (Serial) {
		Serial.println(message);
	}
}

void logMessage(const String& message) {
	if (Serial) {
		Serial.println(message);
	}
}
