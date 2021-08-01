#pragma once

#include "waterSensor.h"
#include "relay.h"

class Controller {
public:
	Controller(WaterSensor* tankWaterSensor, WaterSensor* wellWaterSensor, Relay* pumpRelay);
	void Step();
private:
	WaterSensor* _tankWaterSensor;
	WaterSensor* _wellWaterSensor;
	Relay* _pumpRelay;
	unsigned long _waitingStartTime;
	bool _waitingToFill = false;
};
