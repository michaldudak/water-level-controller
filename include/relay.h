#pragma once

class Relay {
public:
	Relay(byte pin, bool activateByHighSignal = false);
	void Activate();
	void Deactivate();
	bool IsActive();

private:
	byte _pin;
	byte _activationSignal;
	byte _deactivationSignal;
	bool _isActive;
};
