#ifndef ESCALONATOR_H
#define ESCALONATOR_H

#include "types.h"
#include "clock.h"
#include "fifo.h"
#include "usecase.h"
#include "eventqueue.h"

class Escalonator {
public:
    Escalonator();
    ~Escalonator();

    void addEvent(double time, State code, Patient* patient = nullptr);
    Event* getNextEvent();
    bool isEmpty() const;
    void checkQueues(UseCase* useCase, double simulationTime);

private:
    EventQueue eventQueue;
};

#endif // ESCALONATOR_H