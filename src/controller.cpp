#include <arduino.h>
#include "../include/controller.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"

const unsigned long WAIT_TIME = 60 * 60 * 1000UL; // 60 minutes
const unsigned long OVEREMPTYING_TIME = 2 * 60 * 1000UL; // 2 minutes

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
			if (_pumpRelay->IsActive()) {
				// Keep the pump running for OVEREMPTYING_TIME to avoid another positive
				// sensor readout in short succession.
				if (!_overemptying) {
					_overemptying = true;
					_overemptyingStartTime = millis();
				} else if (millis() > _overemptyingStartTime + OVEREMPTYING_TIME) {
					_pumpRelay->Deactivate();
					_waitingToFill = false;
					_overemptying = false;
				}
			}

			break;

		case WaterLevel::Low:
			// If water level is low, wait for WAIT_TIME before activating the pump to avoid
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
