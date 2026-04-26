#include <iostream>

#include "SimManager.h"

static const int TOTAL_HOURS_SIM = 72;
static const int MINS_PER_HOUR = 60;
static const int TOTAL_MINS_SIM = 72 * MINS_PER_HOUR;

static const int DEFAULT_NUM_TRUCKS = 40;
static const int DEFAULT_NUM_STATIONS = 3;

int main()
{
    // TODO: Read in configuration
    std::shared_ptr<Coordinator> coordinator = std::make_shared<Coordinator>(DEFAULT_NUM_STATIONS);
    SimManager simManager(DEFAULT_NUM_TRUCKS, coordinator);

    int currentMinute = 0;
    while (currentMinute<TOTAL_MINS_SIM) {
        currentMinute++;

        simManager.tick();
        if (!(currentMinute%MINS_PER_HOUR)) {
            simManager.print_statistics();
        }
    }
    simManager.print_metrics();

    return 0;
}