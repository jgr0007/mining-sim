#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include <vector>

#include "Site.h"
#include "Truck.h"

class SimManager {
public:
    SimManager(int numTrucks, int numSites);

    /**
    * @brief Perform one minute of simulation.
    * 
    * Each tick executes truck state logic.
    */
    void tick();
    
    void print_statistics();

    const Truck& get_truck(int truckId);
    const Site& get_site(int sitedId);
private:
    std::vector<Truck> trucks;
    std::vector<Site> sites;
};

#endif // SIM_MANAGER_H