#pragma once

enum class WaterLevel : byte {
	Empty = 0,
	Low = 1,
	High = 2,
	Full = 3
};

class WaterSensor {
public:
	/**
	 * Creates a new instance of WaterSensor class
	 * @param lowLevelPin - pin number connected to low water level sensor
	 * @param midLevelPin - pin number connected to middle water level sensor
	 * @param highLevelPin - pin number connected to high water level sensor
	 */
	WaterSensor(byte lowLevelPin, byte midLevelPin, byte highLevelPin);
	WaterLevel ReadLevel();
	WaterLevel GetPreviousLevel();

private:
	byte _lowPin;
	byte _midPin;
	byte _highPin;
	byte _signal;
	WaterLevel _lastReading;
	WaterLevel _previousLevel;

	WaterLevel GetCurrentReading();
};

