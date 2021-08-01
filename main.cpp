#include <arduino.h>
#include "include/constants.h"
#include "include/waterSensor.h"
#include "include/relay.h"
#include "include/controller.h"

const unsigned int STEP_DELAY = 10 * 1000; // 10 seconds;

Controller* controller;

void setup() {
	WaterSensor* wellSensor = new WaterSensor(SENS_WELL_LOW, SENS_WELL_MID, SENS_WELL_HIGH);
	WaterSensor* tankSensor = new WaterSensor(SENS_TANK_LOW, SENS_TANK_MID, SENS_TANK_HIGH);

	Relay* pumpRelay = new Relay(RELAY_PUMP);
	/* TODO: to be added later
	Relay* tankValveRelay = new Relay(RELAY_VALVE_TANK);
	Relay* outValveRelay = new Relay(RELAY_VALVE_OUT); */

	controller = new Controller(tankSensor, wellSensor, pumpRelay);
}

void loop() {
	controller->Step();
	delay(STEP_DELAY);
}
