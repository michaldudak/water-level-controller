#include <arduino.h>
#include "../include/summerPumpController.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"
#include "../include/log.h"

const unsigned long WAIT_TIME = 60 * 60 * 1000UL; // 60 minutes
const unsigned long OVEREMPTYING_TIME = 2 * 60 * 1000UL; // 2 minutes

SummerPumpController::SummerPumpController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay) {
	_tankWaterSensor = tankWaterSensor;
	_wellWaterSensor = wellWaterSensor;
	_pumpRelay = pumpRelay;
}

void SummerPumpController::Step() {
	WaterLevel tankLevel = _tankWaterSensor->ReadLevel();
	WaterLevel wellLevel = _wellWaterSensor->ReadLevel();

	logMessage("Tank level:");
	logMessage(String(static_cast<int>(tankLevel)));

	logMessage("Well level:");
	logMessage(String(static_cast<int>(wellLevel)));

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
			if (tankLevel == WaterLevel::High) {
				// Pump will be started when well water level is higher.
				break;
			}

			if (tankLevel == WaterLevel::Full) {
				// If the tank is full, it'll likely overflow to the well.
				// The pump must be started immediately.
				this->_pumpRelay->Activate();
				break;
			}

			// If water level in both the well and the tank is low,
			// wait for WAIT_TIME before activating the pump to avoid
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
