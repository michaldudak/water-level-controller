#include <arduino.h>
#include "include/constants.h"
#include "include/log.h"
#include "include/waterSensor.h"
#include "include/relay.h"
#include "include/summerPumpController.h"
#include "include/summerValveController.h"
#include "include/winterPumpController.h"
#include "include/winterValveController.h"
#include "include/safetyGuard.h"

const unsigned int STEP_DELAY = 10 * 1000; // 10 seconds;

PumpController* pumpController;
ValveController* valveController;
SafetyGuard* safetyGuard;

void setup() {
	initializeSerialLogger();

	WaterSensor* wellSensor = new WaterSensor(SENS_WELL_LOW, SENS_WELL_MID, SENS_WELL_HIGH);
	WaterSensor* tankSensor = new WaterSensor(SENS_TANK_LOW, SENS_TANK_MID, SENS_TANK_HIGH);

	Relay* pumpRelay = new Relay(RELAY_PUMP);
	Relay* tankValveRelay = new Relay(RELAY_VALVE_TANK);
	Relay* outValveRelay = new Relay(RELAY_VALVE_OUT);

	// pumpController = new SummerPumpController(tankSensor, wellSensor, pumpRelay);
	// valveController = new SummerValveController(tankSensor, wellSensor, pumpRelay, tankValveRelay, outValveRelay);

	// Winter is coming
	pumpController = new WinterPumpController(wellSensor, pumpRelay);
	valveController = new WinterValveController(pumpRelay, outValveRelay);

	safetyGuard = new SafetyGuard(pumpRelay, tankValveRelay, outValveRelay);

	logMessage("Setup complete");
}

void loop() {
	logMessage("Starting evaluation");
	logMessage(String(millis()));
	pumpController->Step();
	valveController->Step();
	safetyGuard->EnsureWaterFlow();
	delay(STEP_DELAY);
}
