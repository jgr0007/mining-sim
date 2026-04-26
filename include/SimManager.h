#ifndef SIM_MANAGER_H
#define SIM_MANAGER_H

#include <vector>

#include "Station.h"
#include "Truck.h"

class SimManager {
public:
    SimManager(int numTrucks, int numStations);

    /**
    * @brief Perform one minute of simulation.
    * 
    * Each tick executes truck state logic.
    */
    void tick();
    
    void print_statistics();

    const Truck& get_truck(int truckId);
    const Station& get_station(int stationdId);
private:
    std::vector<Truck> trucks;
    std::vector<Station> stations;
};

#endif // SIM_MANAGER_H