#include "../include/safetyGuard.h"

SafetyGuard::SafetyGuard(Relay* pumpRelay, Relay* tankValveRelay, Relay* outValveRelay) {
	_pumpRelay = pumpRelay;
	_tankValveRelay = tankValveRelay;
	_outValveRelay = outValveRelay;
}

void SafetyGuard::EnsureWaterFlow() {
	if (_pumpRelay->IsActive() && !_tankValveRelay->IsActive() && !_outValveRelay->IsActive()) {
		_pumpRelay->Deactivate();
	}
}
