#include <iomanip> 
#include <iostream>

#include "SimManager.h"

SimManager::SimManager(int numTrucks, int numStations)
{
    for (int i=0; i<numTrucks; i++) {
        trucks.emplace_back(Truck(i));
    }
    for (int i=0; i<numStations; i++) {
        stations.emplace_back(Station(i));
    }
}

void SimManager::tick()
{
    for (Truck &truck : trucks) {
        // TODO: Make decision for truck
    }
    for (Station &station : stations) {
        // TODO: Get station updates.
    }
}

void SimManager::print_statistics()
{
    int trucksMining{0};
    int truckTraveling{0};
    int trucksWaiting{0};
    int trucksUnloading{0};

    for (const Truck &truck : trucks) {
        if (truck.get_status() == TRUCK_STATUS_MINING) {
            trucksMining++;
        } else if (truck.get_status() == TRUCK_STATUS_TRAVEL_TO_SITE || truck.get_status() == TRUCK_STATUS_TRAVEL_TO_MINE) {
            truckTraveling++;
        } else if (truck.get_status() == TRUCK_STATUS_WAITING) {
            trucksWaiting++;
        } else if (truck.get_status() == TRUCK_STATUS_UNLOADING) {
            trucksUnloading++;
        } else { //truck.get_status() == TRUCK_STATUS_UNKNOWN
            std::cout << "Error in sim - truck reached unknown state!\n";
            std::abort();
        }
    }

    int stationsUnused{0};
    int stationsBusy{0};

    for (const Station &station : stations) {
        if (station.get_waiting()) {
            stationsBusy++;
        } else {
            stationsUnused++;
        }
    }

    // 3. Print Headers
    std::cout << "Current Statistics\n********************************";
    const int colWidth = 14;
    const std::vector<std::string> headers = {
        "TRUCKS MINING",
        "TRUCKS IN TRANSIT",
        "TRUCKS WAITING",
        "TRUCKS_UNLOADING",
        "SITES IDLE", 
        "SITES BUSY"};
    for (const auto& h : headers) {
        std::cout << std::left << std::setw(colWidth) << h;
    }
    std::cout << "\n" << std::string(colWidth * 6, '-') << "\n";

    // 4. Print Rows with Formatting
    std::cout << std::left << std::setw(colWidth) << trucksMining
        << std::left << std::setw(colWidth) << truckTraveling
        << std::left << std::setw(colWidth) << trucksWaiting
        << std::left << std::setw(colWidth) << trucksUnloading
        << std::left << std::setw(colWidth) << stationsUnused
        << std::left << std::setw(colWidth) << stationsBusy 
        << "\n";
}

const Truck& SimManager::get_truck(int truckId)
{
    return trucks[truckId];
}
const Station& SimManager::get_station(int stationId)
{
    return stations[stationId];
}