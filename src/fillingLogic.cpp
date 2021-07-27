#include <arduino.h>
#include "../include/fillingLogic.h"
#include "../include/waterSensor.h"

void decide(WaterSensor tankWaterSensor, WaterSensor wellWaterSensor) {
	WaterLevel tankLevel = tankWaterSensor.ReadLevel();
	WaterLevel wellLevel = wellWaterSensor.ReadLevel();

	// TODO: figure out what to do
}
