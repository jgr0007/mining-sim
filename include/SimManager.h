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
    
    void print_statistics();
    void print_metrics();
private:
    std::vector<Truck> trucks;
    std::shared_ptr<Coordinator> coordinator;
    int tick_count;
};

#endif // SIM_MANAGER_H