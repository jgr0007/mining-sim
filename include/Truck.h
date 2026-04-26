#ifndef TRUCK_H
#define TRUCK_H

enum TRUCK_STATUS {
    TRUCK_STATUS_UNKNOWN = 0,
    TRUCK_STATUS_MINING = 1,
    TRUCK_STATUS_TRAVEL_TO_SITE = 2,
    TRUCK_STATUS_WAITING = 3,
    TRUCK_STATUS_UNLOADING = 4,
    TRUCK_STATUS_TRAVEL_TO_MINE = 5
};

class Truck {
public:
    Truck(int _id);
    TRUCK_STATUS get_status() const;
    int get_id() const;

private:
    int id;
    TRUCK_STATUS status;
    int mining_progress_min;
    int travel_progress_min;
    int unload_progress_min;
};

#endif // TRUCK_H