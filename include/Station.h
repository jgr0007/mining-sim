#ifndef SITE_H
#define SITE_H

#include <queue>

#include "Truck.h"

class Station {
public:
    Station(int _id);
    int get_id() const;
    int get_waiting() const;
    void finish_unload();
    void add_to_queue(int truckId);
private:
    int id;
    std::queue<int> trucks; // Truck IDs
};

#endif // SITE_H