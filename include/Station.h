#ifndef SITE_H
#define SITE_H

#include <queue>

#include "Metrics.h"

class Station {
public:
    explicit Station(int _id);
    
    /**
    * @brief Get number of trucks in line.
    * 
    * Any truck in line is "waiting", even the truck first in
    * line (currently unloading).
    *
    * @return number of trucks waiting at this station.
    */
    int get_waiting() const;

    /**
    * @brief Signal truck done unloading.
    * 
    * The truck leaves this station and is no longer in line.
    */
    void finish_unload();

    /**
    * @brief Add a truck to the line.
    * 
    * The station records that this truck is in line to unload.
    *
    * @param truckId truck to add to queue.
    */
    void add_to_queue(int truckId);

    /**
    * @brief Retrieve the truckID of the first truck in line.
    * 
    * This is the truck that is ready to begin unloading.
    *
    * @return truckId of first truck in line.
    */
    int next_truck();

    /**
    * @brief Record metrics.
    * 
    * Each call to this function records usage statistics
    * for this station.
    */
    void increment_metrics();

    /**
    * @brief Retrieve station metrics.
    * 
    * Retrieve summary of station usage statistics..
    *
    * @return metrics for this station.
    */
    StationMetrics get_metrics() const;
private:
    int id;
    std::queue<int> trucks; // Truck IDs
    StationMetrics station_metrics;
};

#endif // SITE_H