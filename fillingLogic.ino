void decide() {
    byte wellLevel = getWellWaterLevel();
    byte tankLevel = getTankWaterLevel();

    // nothing to do, well is empty
    if (wellLevel == 0) {
        closeAll();
        return;
    }

    // water level too high - either a strong rain or 
    // a tank overflow
    if (wellLevel == 3) {
        openOutValve();
        delay(200);
        startPump();
    }

    // TODO: low-medium water level in the well - decide what to do
}