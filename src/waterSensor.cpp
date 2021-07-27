#include <arduino.h>
#include "../include/waterSensor.h"

WaterSensor::WaterSensor(byte lowLevelPin, byte midLevelPin, byte highLevelPin) {
	this->_lowPin = lowLevelPin;
	this->_midPin = midLevelPin;
	this->_highPin = highLevelPin;

	pinMode(this->_lowPin, INPUT_PULLUP);
	pinMode(this->_midPin, INPUT_PULLUP);
	pinMode(this->_highPin, INPUT_PULLUP);
}

WaterLevel WaterSensor::ReadLevel() {
	// TODO: verify if sensors work correctly by checking lower ones
	if (digitalRead(this->_highPin) == LOW) {
		return WaterLevel::Full;
	}

	if (digitalRead(this->_midPin) == LOW) {
		return WaterLevel::High;
	}

	if (digitalRead(this->_lowPin) == LOW) {
		return WaterLevel::Low;
	}

	return WaterLevel::Empty;
}
