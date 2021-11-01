#pragma once

#include "valveController.h"
#include "waterSensor.h"
#include "relay.h"

class SummerValveController: public ValveController {
public:
	SummerValveController(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay);
	virtual void Step();
private:
	WaterSensor* _tankWaterSensor;
	WaterSensor* _wellWaterSensor;
	Relay* _pumpRelay;
	Relay* _tankValveRelay;
	Relay* _outValveRelay;
	bool _overfilling = false;
	unsigned long _overfillingStartTime;
};
