#include <iostream>

#include "Truck.h"

Truck::Truck(int _id, const std::shared_ptr<Coordinator> &_coordinator)
:
id(_id),
coordinator(_coordinator)
{
    start_mining();
}

int Truck::get_id() const
{
    return id;
}

TRUCK_STATUS Truck::get_status() const
{
    return status;
}

void Truck::work()
{
    if (status==TRUCK_STATUS_MINING) {
        mining_progress_minutes++;
        truck_metrics.time_mining++;
        if (mining_progress_minutes==expected_mining_time) {
            travel_to_station();
        }
    } else if (status==TRUCK_STATUS_TRAVEL_TO_STATION) {
        travel_progress_minutes++;
        truck_metrics.time_traveling++;
        if (travel_progress_minutes==TOTAL_TIME_TO_TRAVEL_MINS) {
            arrive_at_station();
        }
    } else if (status==TRUCK_STATUS_WAITING) {
        truck_metrics.time_waiting++;
        if (coordinator->check_if_truck_unloadable(id)) {
            start_unloading();
        }
    } else if (status==TRUCK_STATUS_UNLOADING) {
        unload_progress_minutes++;
        if (unload_progress_minutes==TOTAL_TIME_TO_UNLOAD_MINS) {
            travel_to_mine();
        }
    } else if (status==TRUCK_STATUS_TRAVEL_TO_MINE) {
        travel_progress_minutes++;
        truck_metrics.time_traveling++;
        if (travel_progress_minutes==TOTAL_TIME_TO_TRAVEL_MINS) {
            start_mining();
        }
    } else { //status == TRUCK_STATUS_UNKNOWN
        std::cout << "Truck broke down, reached unknown state!\n";
        std::abort();
    }
}

void Truck::start_mining()
{
    reset_progress();
    status = TRUCK_STATUS_MINING;
    expected_mining_time = coordinator->get_mining_duration();
    std::cout << "Truck: " << id << " started mining with expected duration: " << expected_mining_time << " minutes." << std::endl;
}

void Truck::travel_to_station()
{
    reset_progress();
    status = TRUCK_STATUS_TRAVEL_TO_STATION;
    destination_unload = coordinator->get_destination(id);
    std::cout << "Truck: " << id << " finished mining, and heading to station: " << destination_unload << "." << std::endl;
}

// NOTE:
// - This implementation of arrival mechanic means that a truck will always
//   take one `tick()` (which is currently one minute) to transition from
//   _driving_ to the unload station to _unloading_ at the unload station,
//   even if the station is empty when the truck arrives.
//  - The requirements doc doesn't specify this behvior, so I think this is a
//  reasonable choice. Would probably take time to configure the truck for 
//  unloading in the real world.
void Truck::arrive_at_station()
{
    std::cout << "Truck: " << id << " arrived at station: " << destination_unload << std::endl; 
    if (coordinator->station_free(destination_unload)) {       
        coordinator->get_in_line(id, destination_unload);
        start_unloading();
    } else {
        coordinator->get_in_line(id, destination_unload);
        start_waiting();
    }
}

void Truck::start_waiting()
{
    reset_progress();
    status = TRUCK_STATUS_WAITING;
    std::cout << "Truck: " << id << " started waiting in line." << std::endl; 
}

void Truck::start_unloading()
{
    reset_progress();
    status = TRUCK_STATUS_UNLOADING;
    std::cout << "Truck: " << id << " began unloading." << std::endl; 
}

void Truck::travel_to_mine()
{
    reset_progress();
    coordinator->end_unload(id);
    status = TRUCK_STATUS_TRAVEL_TO_MINE;
    std::cout << "Truck: " << id << " heading back to the mine." << std::endl; 
}

void Truck::reset_progress()
{
    status = TRUCK_STATUS_UNKNOWN;
    mining_progress_minutes = 0;
    expected_mining_time = 0;
    travel_progress_minutes = 0;
    unload_progress_minutes = 0;
    destination_unload = -1;
}

TruckMetrics Truck::get_metrics() const
{
    return truck_metrics;
}
