#include <arduino.h>
#include "../include/winterPumpController.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"

WinterPumpController::WinterPumpController(WaterSensor* wellWaterSensor, Relay* pumpRelay) {
	_wellWaterSensor = wellWaterSensor;
	_pumpRelay = pumpRelay;
}

void WinterPumpController::Step() {
	WaterLevel wellLevel = _wellWaterSensor->ReadLevel();

	if (wellLevel == WaterLevel::Empty) {
		_pumpRelay->Deactivate();
	} else if (wellLevel == WaterLevel::Full || wellLevel == WaterLevel::High) {
		_pumpRelay->Activate();
	}
}
