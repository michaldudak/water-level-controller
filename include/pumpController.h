#pragma once

#include "waterSensor.h"
#include "relay.h"

class PumpController {
public:
	PumpController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay);
	void Step();
private:
	WaterSensor* _tankWaterSensor;
	WaterSensor* _wellWaterSensor;
	Relay* _pumpRelay;
	bool _waitingToFill = false;
	unsigned long _waitingStartTime;
	bool _overemptying = false;
	unsigned long _overemptyingStartTime;
};
