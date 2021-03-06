#pragma once

#include <arduino.h>

#define SENS_WELL_LOW  2
#define SENS_WELL_MID  3
#define SENS_WELL_HIGH 4

#define SENS_TANK_LOW  5
#define SENS_TANK_MID  6
#define SENS_TANK_HIGH 7

#define SELECT_MODE_0 8
#define SELECT_MODE_1 9

#define RELAY_VALVE_OUT  A3
#define RELAY_VALVE_TANK A4
#define RELAY_PUMP       A5

#define MODE_OFF  0
#define MODE_TANK 1
#define MODE_OUT  2
#define MODE_AUTO 3
