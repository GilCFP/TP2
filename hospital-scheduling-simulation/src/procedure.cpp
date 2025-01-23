#include "../include/procedure.h"
#include <stdexcept>

Procedure::Procedure(int units, double averageTime)
    : total(units), available(units), averageTime(averageTime) {}

int Procedure::getAvaliableUnits() const
{
    return available;
}

int Procedure::getUnits() const
{
    return total;
}

double Procedure::getAverageTime() const
{
    return averageTime;
}

void Procedure::startProcedure()
{
    if (available == 0)
    {
        throw std::logic_error("No units available");
    }
    available--;
}

void Procedure::endProcedure()
{
    if (available == total)
    {
        throw std::logic_error("All units are already available");
    }
    available++;
}

void Procedure::setUnits(int units){
    total = units;
}

void Procedure::setAverageTime(double averageTime){
    this->averageTime = averageTime;
}

int Procedure::getEndTime(int quantity)
{
    return averageTime * quantity;
}
