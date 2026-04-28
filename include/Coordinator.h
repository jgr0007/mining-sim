#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <unordered_map>
#include <unordered_set>

#include "Station.h"

class Coordinator {
public:
    explicit Coordinator(int numStations);

    /**
    * @brief Get unload destination for a truck.
    * 
    * Send this truck to the destination that has the least amount of trucks queued or heading there.
    * This is a rough guess at efficient routing since this approach doesn't take into account
    * how close the trucks are to arriving at the station. But since each truck always takes
    * exactly 30 minutes to get to any station, and always takes exactly 5 minutes to unload, this
    * approach is probably super good enough.
    * 
    * @param truckId truck ID to be routed to an unload station.
    * @param stationsBusy number of stations currently in-use.
    *
    * @return The ID of the unload station to visit.
    */
    int get_destination(int truckId);

    /**
    * @brief Determine how long a truck should mine.
    * 
    * Generate a random number of minutes.
    * This simulates how long the truck will mine.
    *
    * @return Number of minutes between 60 and 300 that the truck will mine for.
    */
    int get_mining_duration();
   
    /**
    * @brief Determine if a station is free to immediately begin unloading.
    * 
    * This function called by arriving trucks to see whether they can
    * begin unloading or must get in line.
    *
    * @param stationId station to check status of.
    *
    * @return True if the station is has no trucks currently queued or unloading.
    */
    bool station_free(int stationId);

    /**
    * @brief Determine if truck is first in line.
    * 
    * If truck is first in line at the station, it can begin unloading.
    *
    * @param truckId truck to check status of.
    *
    * @return True if the truck is first in line.
    */
    bool check_if_truck_unloadable(int truckId);

    /**
    * @brief Finish unloading a truck.
    * 
    * Tells the coordinator that the truck is heading back to the mine.
    * Coordinator tells the station that the truck is leaving.
    *
    * @param truckId truck that is done unloading.
    *
    */
    void end_unload(int truckId);

    /**
    * @brief Queue a truck to begin waiting.
    * 
    * Tells the coordinator which station the truck is waiting at.
    * Coordinator tells the station that it has a new truck in line.
    *
    * @param truckId truck that begins waiting.
    * @param stationId station where truck gets in line.
    *
    */
    void get_in_line(
        int truckId, 
        int stationId);


    /**
    * @brief Record metrics.
    * 
    * Each call updates station metrics for later reporting.
    *
    */
    void increment_station_metrics();

    /**
    * @brief Get per-station metrics.
    * 
    * This function returns metrics for each unload station.
    * Additionally this function calculates simple usage statistics.
    * 
    * @param stationsUnused number of stations currently unused.
    * @param stationsBusy number of stations currently in-use.
    */
    void get_station_metrics(
        int &stationsUnused, 
        int &stationsBusy, 
        std::vector<StationMetrics> &stationMetrics);
private:
    std::vector<Station> stations;
    std::unordered_map<int,int> trucksAtStations; // truckID:stationID
    std::vector<std::unordered_set<int>> trucksDestinedForStations;// set of truck IDs destined for each station (each vector entry is a stationID)
};

#endif // COORDINATOR_H