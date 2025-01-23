#ifndef EVENT_H
#define EVENT_H
#include "patient.h"
struct Event
{
    double time;
    State code;
    Patient *patient;

    bool operator<(const Event &other) const
    {
        return time > other.time;
    }
};
#endif 