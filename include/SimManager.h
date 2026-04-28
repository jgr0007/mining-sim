#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include <vector>

#include "Coordinator.h"
#include "Station.h"
#include "Truck.h"

class SimManager {
public:
    explicit SimManager(int numTrucks, const std::shared_ptr<Coordinator> &_coordinator);

    /**
    * @brief Perform one minute of simulation.
    * 
    * Each tick executes truck state logic.
    */
    void tick();
    
    /**
    * @brief Print real-time statistics .
    * 
    * High-level statistics meant to give awareness during sim.
    *
    */
    void print_statistics();
    
    /**
    * @brief Print summary statistics.
    * 
    * Per-truck and per-station statistics meant to be
    * reported at end of sim.
    *
    */
    void print_metrics();
private:
    std::vector<Truck> trucks;
    std::shared_ptr<Coordinator> coordinator;
    int tick_count;
};

#endif // SIM_MANAGER_H