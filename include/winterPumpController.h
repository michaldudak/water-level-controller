#pragma once

#include "pumpController.h"
#include "waterSensor.h"
#include "relay.h"

class WinterPumpController: public PumpController {
public:
	WinterPumpController(WaterSensor* wellWaterSensor, Relay* pumpRelay);
	virtual void Step();
private:
	WaterSensor* _wellWaterSensor;
	Relay* _pumpRelay;
};
