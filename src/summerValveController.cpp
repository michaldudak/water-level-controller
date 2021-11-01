#include <arduino.h>
#include "../include/summerValveController.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"
#include "../include/log.h"

const unsigned long OVERFILLING_TIME = 2 * 60 * 1000UL; // 2 minutes

SummerValveController::SummerValveController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay) {
	_tankWaterSensor = tankWaterSensor;
	_wellWaterSensor = wellWaterSensor;
	_pumpRelay = pumpRelay;
	_tankValveRelay = tankValveRelay;
	_outValveRelay = outValveRelay;
}

void SummerValveController::Step() {
	WaterLevel tankLevel = _tankWaterSensor->ReadLevel();
	WaterLevel wellLevel = _wellWaterSensor->ReadLevel();
	bool isPumpRunning = _pumpRelay->IsActive();

	if (!isPumpRunning) {
		logMessage("Pump not running. Closing valves.");
		_tankValveRelay->Deactivate();
		_outValveRelay->Deactivate();
		return;
	}

	if (tankLevel == WaterLevel::Empty || tankLevel == WaterLevel::Low) {
		logMessage("Tank is empty or low. Opening tank valve.");
		_overfilling = false;
		_tankValveRelay->Activate();
		delay(500);
		_outValveRelay->Deactivate();
		return;
	}

	if (tankLevel == WaterLevel::High && _tankWaterSensor->GetPreviousLevel() == WaterLevel::Low) {
		if (!_overfilling) {
			logMessage("Tank level is high. Beginning tank overfill.");
			_overfilling = true;
			_overfillingStartTime = millis();
		}

		if (_overfillingStartTime + OVERFILLING_TIME > millis()) {
			logMessage("Overfill complete. Opening out valve.");
			_outValveRelay->Activate();
			delay(500);
			_tankValveRelay->Deactivate();
		}

		return;
	}

	if (tankLevel == WaterLevel::Full) {
		logMessage("Tank is full. Opening out valve.");
	} else {
		logMessage("Tank level went from full to high. Keeping the out valve open.");
	}

	_outValveRelay->Activate();
	delay(500);
	_tankValveRelay->Deactivate();
	_overfilling = false;
}
