#pragma once

#include "waterSensor.h"
#include "relay.h"

class ValveController {
public:
	ValveController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay);
	void Step();
private:
	WaterSensor* _tankWaterSensor;
	WaterSensor* _wellWaterSensor;
	Relay* _pumpRelay;
	Relay* _tankValveRelay;
	Relay* _outValveRelay;
	bool _overfilling = false;
	unsigned long _overfillingStartTime;
};
