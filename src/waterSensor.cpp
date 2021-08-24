#include <arduino.h>
#include "../include/waterSensor.h"

WaterSensor::WaterSensor(byte lowLevelPin, byte midLevelPin, byte highLevelPin) {
	this->_lowPin = lowLevelPin;
	this->_midPin = midLevelPin;
	this->_highPin = highLevelPin;

	pinMode(this->_lowPin, INPUT_PULLUP);
	pinMode(this->_midPin, INPUT_PULLUP);
	pinMode(this->_highPin, INPUT_PULLUP);

	WaterLevel firstReading = GetCurrentReading();
	_lastReading = firstReading;
	_previousLevel = firstReading;
}

WaterLevel WaterSensor::ReadLevel() {
	WaterLevel currentLevel = GetCurrentReading();
	if (currentLevel != _lastReading) {
		_previousLevel = _lastReading;
		_lastReading = currentLevel;
	}

	return currentLevel;
}

WaterLevel WaterSensor::GetPreviousLevel() {
	return _previousLevel;
}

WaterLevel WaterSensor::GetCurrentReading() {
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
