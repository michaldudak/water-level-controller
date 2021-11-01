#include <arduino.h>
#include "../include/winterValveController.h"
#include "../include/waterSensor.h"
#include "../include/relay.h"

WinterValveController::WinterValveController(Relay* pumpRelay, Relay* outValveRelay) {
	_pumpRelay = pumpRelay;
	_outValveRelay = outValveRelay;
}

void WinterValveController::Step() {
	if (_pumpRelay->IsActive()) {
		_outValveRelay->Activate();
	} else {
		delay(500);
		_outValveRelay->Deactivate();
	}
}
