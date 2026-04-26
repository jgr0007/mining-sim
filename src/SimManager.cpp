#include <iomanip> 
#include <iostream>

#include "SimManager.h"

SimManager::SimManager(int numTrucks, int numSites)
{
    for (int i=0; i<numTrucks; i++) {
        trucks.emplace_back(Truck(i));
    }
    for (int i=0; i<numSites; i++) {
        sites.emplace_back(Site(i));
    }
}

void SimManager::tick()
{
    for (Truck &truck : trucks) {
        // TODO: Make decision for truck
    }
    for (Site &site : sites) {
        // TODO: Get site updates.
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

    int sitesUnused{0};
    int sitesBusy{0};

    for (const Site &site : sites) {
        if (site.get_waiting()) {
            sitesBusy++;
        } else {
            sitesUnused++;
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
        << std::left << std::setw(colWidth) << sitesUnused
        << std::left << std::setw(colWidth) << sitesBusy 
        << "\n";
}

const Truck& SimManager::get_truck(int truckId)
{
    return trucks[truckId];
}
const Site& SimManager::get_site(int siteId)
{
    return sites[siteId];
}