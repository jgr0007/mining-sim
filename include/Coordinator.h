#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <unordered_map>

#include "Station.h"

class Coordinator {
public:
    explicit Coordinator(int numStations);

    int get_destination();
    int get_mining_duration();
    bool station_free(int stationId);
    bool check_if_truck_unloadable(int truckId);
    void end_unload(int truckId);
    void get_in_line(int truckId, int stationId);

    void increment_station_metrics();
    void get_station_metrics(int &stationsUnused, int &stationsBusy, std::vector<StationMetrics> &stationMetrics);
private:
    std::vector<Station> stations;
    std::unordered_map<int,int> trucksAtStations;
};

#endif // COORDINATOR_H