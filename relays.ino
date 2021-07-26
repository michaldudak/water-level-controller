#include "constants.h"

void closeAll() {
    digitalWrite(RELAY_PUMP, LOW);
    digitalWrite(RELAY_VALVE_OUT, LOW);
    digitalWrite(RELAY_VALVE_TANK, LOW);
}

void openTankValve() {
    digitalWrite(RELAY_VALVE_TANK, HIGH);
}

void closeTankValve() {
    digitalWrite(RELAY_VALVE_TANK, LOW);
}

void openOutValve() {
    digitalWrite(RELAY_VALVE_OUT, HIGH);
}

void closeOutValve() {
    digitalWrite(RELAY_VALVE_OUT, LOW);
}

void startPump() {
    digitalWrite(RELAY_PUMP, HIGH);
}

void stopPump() {
    digitalWrite(RELAY_PUMP, LOW);
}
