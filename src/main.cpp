#include <iostream>

#include "SimManager.h"

const int TOTAL_HOURS_SIM = 72;
const int MINS_PER_HOUR = 60;
const int TOTAL_MINS_SIM = 72 * MINS_PER_HOUR;

int main()
{
    // (1) Read in configuration
    // (2) Instantiate objects
    SimManager simManager(3,3);
    // (3) Run sim.

    int currentMin = 0;
    while (currentMin<TOTAL_MINS_SIM) {
        currentMin++;

        // (1) Tick
        simManager.tick();
        // (2) Print statistics once per hour
        if (!(currentMin%MINS_PER_HOUR)) {
            simManager.print_statistics();
        }
    }
    // (4) Output report

    return 0;
}