#include "constants.h"

byte getMode() {
  return digitalRead((SELECT_MODE_1 << 1) + SELECT_MODE_0);
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
