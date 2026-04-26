#include "Station.h"

Station::Station(int _id)
:
id(_id)
{
}

int Station::get_id() const
{
    return id;
}

int Station::get_waiting() const
{
    return trucks.size();
}

void Station::finish_unload()
{
    trucks.pop();
}

void Station::add_to_queue(int truckId)
{
    trucks.push(truckId);
}