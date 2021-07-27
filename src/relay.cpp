#include <arduino.h>
#include "../include/relay.h"

Relay::Relay(byte pin, bool activateByHighSignal) {
	this->_pin = pin;
	this->_isActive = false;
	this->_activationSignal = activateByHighSignal ? HIGH : LOW;
	this->_deactivationSignal = activateByHighSignal ? LOW : HIGH;

	pinMode(pin, OUTPUT);
	digitalWrite(pin, this->_deactivationSignal);
}

void Relay::Activate() {
	this->_isActive = true;
	digitalWrite(this->_pin, this->_activationSignal);
}

void Relay::Deactivate() {
	this->_isActive = false;
	digitalWrite(this->_pin, this->_deactivationSignal);
}
