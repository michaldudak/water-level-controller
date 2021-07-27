//#include <arduino.h>
#include "include/constants.h"
#include "include/waterSensor.h"
#include "include/relay.h"

WaterSensor* wellSensor;
WaterSensor* tankSensor;

void setup() {
	wellSensor = new WaterSensor(SENS_WELL_LOW, SENS_WELL_MID, SENS_WELL_HIGH);
	tankSensor = new WaterSensor(SENS_TANK_LOW, SENS_TANK_MID, SENS_TANK_HIGH);

	Relay* tankValveRelay = new Relay(RELAY_VALVE_TANK);
	Relay* outValveRelay = new Relay(RELAY_VALVE_OUT);
	Relay* pumpRelay = new Relay(RELAY_PUMP);
}

void loop() {

}
