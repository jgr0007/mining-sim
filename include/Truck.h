#ifndef TRUCK_H
#define TRUCK_H

#include <memory>

#include "Coordinator.h"
#include "Metrics.h"

static const int TOTAL_TIME_TO_TRAVEL_MINS = 30;
static const int TOTAL_TIME_TO_UNLOAD_MINS = 5;

enum TRUCK_STATUS {
    TRUCK_STATUS_UNKNOWN = 0,
    TRUCK_STATUS_MINING = 1,
    TRUCK_STATUS_TRAVEL_TO_STATION = 2,
    TRUCK_STATUS_WAITING = 3,
    TRUCK_STATUS_UNLOADING = 4,
    TRUCK_STATUS_TRAVEL_TO_MINE = 5
};

class Truck {
public:
    explicit Truck(int _id, const std::shared_ptr<Coordinator> &_coordinator);
    TRUCK_STATUS get_status() const;
    int get_id() const;
    void work();

    TruckMetrics get_metrics() const;

private:
    void start_mining();
    void travel_to_station();
    void arrive_at_station();
    void start_waiting();
    void start_unloading();
    void travel_to_mine();
    void reset_progress();
    
    const int id;
    TRUCK_STATUS status;

    int mining_progress_minutes;
    int expected_mining_time;
    
    int travel_progress_minutes;
    int unload_progress_minutes;
    int destination_unload;

    std::shared_ptr<Coordinator> coordinator;

    TruckMetrics truck_metrics;
};

#endif // TRUCK_H