#include <arduino.h>
#include "../include/valveController.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"

const unsigned long OVERFILLING_TIME = 2 * 60 * 1000UL; // 2 minutes

ValveController::ValveController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay) {
	_tankWaterSensor = tankWaterSensor;
	_wellWaterSensor = wellWaterSensor;
	_pumpRelay = pumpRelay;
	_tankValveRelay = tankValveRelay;
	_outValveRelay = outValveRelay;
}

void ValveController::Step() {
	WaterLevel tankLevel = _tankWaterSensor->ReadLevel();
	WaterLevel wellLevel = _wellWaterSensor->ReadLevel();
	bool isPumpRunning = _pumpRelay->IsActive();

	if (isPumpRunning) {
		_tankValveRelay->Deactivate();
		_outValveRelay->Deactivate();
		return;
	}

	if (tankLevel == WaterLevel::Empty || tankLevel == WaterLevel::Low) {
		_tankValveRelay->Activate();
		_outValveRelay->Deactivate();
		_overfilling = false;
		return;
	}

	if (tankLevel == WaterLevel::High && _tankWaterSensor->GetPreviousLevel() == WaterLevel::Low) {
		if (!_overfilling) {
			_overfilling = true;
			_overfillingStartTime = millis();
		}

		if (_overfillingStartTime + OVERFILLING_TIME > millis()) {
			_tankValveRelay->Deactivate();
			_outValveRelay->Activate();
		}

		return;
	}

	_tankValveRelay->Deactivate();
	_outValveRelay->Activate();
	_overfilling = false;
}
