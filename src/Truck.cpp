#include "Truck.h"

Truck::Truck(int _id)
:
id(_id)
{
}

int Truck::get_id() const
{
    return id;
}

TRUCK_STATUS Truck::get_status() const
{
    return status;
}