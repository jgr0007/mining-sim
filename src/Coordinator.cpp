#include <limits>
#include <random>

#include "Coordinator.h"

static const int MIN_MINING_TIME_MINUTES = 60;
static const int MAX_MINING_TIME_MINUTES = 300;

Coordinator::Coordinator(int numStations)
{
    for (int i=0; i<numStations; i++) {
        stations.emplace_back(Station(i));
        trucksDestinedForStations.push_back(std::unordered_set<int>{});
    }
}

int Coordinator::get_destination(int truckId)
{
    int shortestWaitQueue = std::numeric_limits<int>::max();
    int destStationId = 0;

    for (int i=0; i<stations.size(); i++) {
        const int stationLine = stations[i].get_waiting();
        const int expectedArrivals = trucksDestinedForStations[i].size();
        const int totalWaitQueue = stationLine+expectedArrivals;

        if (totalWaitQueue==0) {
            destStationId = i;
            break;
        } else if (totalWaitQueue<shortestWaitQueue) {
            shortestWaitQueue = totalWaitQueue;
            destStationId = i;
        }
    }

    trucksDestinedForStations[destStationId].insert(truckId);
    return destStationId;
}

int Coordinator::get_mining_duration()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> distr(MIN_MINING_TIME_MINUTES, MAX_MINING_TIME_MINUTES); 
    return distr(gen);
}

bool Coordinator::station_free(int stationId)
{
    return stations[stationId].get_waiting()==0;
}

bool Coordinator::check_if_truck_unloadable(int truckId)
{
    return stations[trucksAtStations[truckId]].next_truck() == truckId;
}

void Coordinator::end_unload(int truckId)
{
    const int stationId = trucksAtStations[truckId]; 
    stations[stationId].finish_unload();
    trucksAtStations.erase(truckId);
}

void Coordinator::get_in_line(int truckId, int stationId)
{
    stations[stationId].add_to_queue(truckId);
    trucksAtStations[truckId] = stationId;
    // Truck is no longer an expected arrival since it just arrived.
    trucksDestinedForStations[stationId].erase(truckId);
}

void Coordinator::increment_station_metrics()
{
    for (int i=0; i<stations.size(); i++) {
        stations[i].increment_metrics();
    }
}

void Coordinator::get_station_metrics(int &stationsUnused, int &stationsBusy, std::vector<StationMetrics> &stationMetrics)
{
    stationsUnused = 0;
    stationsBusy = 0;
    stationMetrics.clear();
    
    for (const Station &station : stations) {
        if (station.get_waiting()) {
            stationsBusy++;
        } else {
            stationsUnused++;
        }
        stationMetrics.push_back(station.get_metrics());
    }
}