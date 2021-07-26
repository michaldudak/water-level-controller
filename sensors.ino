#include "constants.h"

/**
 * Gets water level in the well.
 * Returns 0-3 (0 - almost empty, 3 - almost full)
 */
byte getWellWaterLevel() {
  // TODO: verify if sensors work correctly by checking lower ones
  if (digitalRead(SENS_WELL_HIGH) == LOW) {
    return 3;
  }

  if (digitalRead(SENS_WELL_MID) == LOW) {
    return 2;
  }

  if (digitalRead(SENS_WELL_LOW) == LOW) {
    return 1;
  }

  return 0;
}

/**
 * Gets water level in the tank.
 * Returns 0-3 (0 - almost empty, 3 - almost full)
 */
byte getTankWaterLevel() {
  // TODO: verify if sensors work correctly by checking lower ones
  if (digitalRead(SENS_TANK_HIGH) == LOW) {
    return 3;
  }

  if (digitalRead(SENS_TANK_MID) == LOW) {
    return 2;
  }

  if (digitalRead(SENS_TANK_LOW) == LOW) {
    return 1;
  }

  return 0;
}