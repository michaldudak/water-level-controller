#include <arduino.h>
#include "../include/controller.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"

const unsigned long WAIT_TIME = 60 * 60 * 1000UL; // 60 minutes

Controller::Controller(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay) {
	_tankWaterSensor = tankWaterSensor;
	_wellWaterSensor = wellWaterSensor;
	_pumpRelay = pumpRelay;
}

void Controller::Step() {
	WaterLevel tankLevel = _tankWaterSensor->ReadLevel();
	WaterLevel wellLevel = _wellWaterSensor->ReadLevel();

	switch (wellLevel) {
		case WaterLevel::Empty:
			_pumpRelay->Deactivate();
			_waitingToFill = false;
			break;

		case WaterLevel::Low:
			// If water level is low, wait for WAIT_TIME before activating the pump, so we avoid
			// turning it on frequently for short periods.
			if (!_waitingToFill) {
				_waitingToFill = true;
				_waitingStartTime = millis();
			} else if (millis() > _waitingStartTime + WAIT_TIME) {
				this->_pumpRelay->Activate();
			}

			break;

		default:
			// If water level is higher, activate the pump immediately.
			_pumpRelay->Activate();
	}
}
