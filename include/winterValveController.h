#pragma once

#include "valveController.h"
#include "waterSensor.h"
#include "relay.h"

class WinterValveController: public ValveController {
public:
	WinterValveController(Relay* pumpRelay, Relay* outValveRelay);
	virtual void Step();
private:
	Relay* _pumpRelay;
	Relay* _outValveRelay;
};
