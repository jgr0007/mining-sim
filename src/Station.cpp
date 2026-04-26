#include "Station.h"

Station::Station(int _id)
:
id(_id)
{
}

int Station::get_waiting() const
{
    return trucks.size();
}

void Station::finish_unload()
{
    trucks.pop();
    station_metrics.trucks_unloaded++;
}

void Station::add_to_queue(int truckId)
{
    trucks.push(truckId);
    station_metrics.longest_unload_line = std::max(station_metrics.longest_unload_line, static_cast<int>(trucks.size()));
}

int Station::next_truck()
{
    if (trucks.size()) {
        return trucks.front();
    } else {
        return -1;
    }
}

void Station::increment_metrics()
{
    if (trucks.size()) {
        station_metrics.time_utilized++;
    } else {
        station_metrics.time_idle++;
    }
}

StationMetrics Station::get_metrics() const
{
    return station_metrics;
}