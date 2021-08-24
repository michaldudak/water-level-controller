#pragma once
#include "../include/relay.h"

class SafetyGuard {
public:
	SafetyGuard(Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay);
	void EnsureWaterFlow();
private:
	Relay* _pumpRelay;
	Relay* _tankValveRelay;
	Relay* _outValveRelay;
};
