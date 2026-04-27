#include <iomanip> 
#include <iostream>

#include "SimManager.h"

SimManager::SimManager(int numTrucks, const std::shared_ptr<Coordinator> &_coordinator)
:
coordinator(_coordinator),
tick_count(0)
{
    for (int i=0; i<numTrucks; i++) {
        trucks.emplace_back(Truck(i, coordinator));
    }
}

void SimManager::tick()
{
    tick_count++;
    for (Truck &truck : trucks) {
        truck.work();
    }
    coordinator->increment_station_metrics();
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
        } else if ((truck.get_status() == TRUCK_STATUS_TRAVEL_TO_STATION) || (truck.get_status() == TRUCK_STATUS_TRAVEL_TO_MINE)) {
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
    std::vector<StationMetrics> metrics{};
    coordinator->get_station_metrics(stationsUnused, stationsBusy, metrics);

    std::cout << "\nEnd of Minute (Tick): " << tick_count << std::endl;
    std::cout << "\n************************************************************************************************************\n";
    const int colWidth = 18;
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

    std::cout << std::left << std::setw(colWidth) << trucksMining
        << std::left << std::setw(colWidth) << truckTraveling
        << std::left << std::setw(colWidth) << trucksWaiting
        << std::left << std::setw(colWidth) << trucksUnloading
        << std::left << std::setw(colWidth) << stationsUnused
        << std::left << std::setw(colWidth) << stationsBusy 
        << "\n";
}

void SimManager::print_metrics()
{
    int stationsUnused{0};
    int stationsBusy{0};
    std::vector<StationMetrics> metrics{};
    coordinator->get_station_metrics(stationsUnused, stationsBusy, metrics);

    std::cout << "\n\n\nEnd of Simulation. " << tick_count << " minutes elapsed." << std::endl;
    std::cout << "\n************************************************************************************************************\n";

    std::cout << "**************** Truck Statistics ****************\n";
    for (const auto &truck : trucks) {
        TruckMetrics truckMetrics = truck.get_metrics();
        std::cout << "Truck " << truck.get_id() << " Stats:\n";
        std::cout << "Minutes Spent Mining: " << truckMetrics.time_mining << std::endl;
        std::cout << "Minutes Spent Traveling: " << truckMetrics.time_traveling << std::endl;
        std::cout << "Minutes Spent Waiting to Unload: " << truckMetrics.time_waiting << std::endl;
        std::cout << "-\n";
    }
    std::cout << "**************** Station Statistics ****************\n";
    int stationId = 0;
    for (const auto &stationMetric: metrics) {
        std::cout << "Station " << stationId << " Stats:\n";
        std::cout << "Total Minutes Utilized: " << stationMetric.time_utilized << std::endl;
        std::cout << "Total Minutes Idle: " << stationMetric.time_idle << std::endl;
        std::cout << "Longest Unload Line: " << stationMetric.longest_unload_line << std::endl;
        std::cout << "Total Trucks Unloaded: " << stationMetric.trucks_unloaded << std::endl;
        std::cout << "-\n";

        stationId++;
    }
    std::cout << "****************************************************\n";
}