#include "Site.h"

Site::Site(int _id)
:
id(_id)
{
}

int Site::get_id() const
{
    return id;
}

int Site::get_waiting() const
{
    return trucks.size();
}

void Site::finish_unload()
{
    trucks.pop();
}

void Site::add_to_queue(int truckId)
{
    trucks.push(truckId);
}