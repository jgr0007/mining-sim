#ifndef SITE_H
#define SITE_H

#include <queue>

#include "Metrics.h"

class Station {
public:
    explicit Station(int _id);
    int get_waiting() const;
    void finish_unload();
    void add_to_queue(int truckId);
    int next_truck();

    void increment_metrics();
    StationMetrics get_metrics() const;
private:
    int id;
    std::queue<int> trucks; // Truck IDs
    StationMetrics station_metrics;
};

#endif // SITE_H