#include "constants.h"

void setupIO() {
  pinMode(SENS_WELL_LOW, INPUT_PULLUP);
  pinMode(SENS_WELL_MID, INPUT_PULLUP);
  pinMode(SENS_WELL_HIGH, INPUT_PULLUP);
  pinMode(SENS_TANK_LOW, INPUT_PULLUP);
  pinMode(SENS_TANK_MID, INPUT_PULLUP);
  pinMode(SENS_TANK_HIGH, INPUT_PULLUP);
  pinMode(SELECT_MODE_0, INPUT_PULLUP);
  pinMode(SELECT_MODE_1, INPUT_PULLUP);
  pinMode(RELAY_VALVE_TANK, OUTPUT);
  pinMode(RELAY_VALVE_OUT, OUTPUT);
}