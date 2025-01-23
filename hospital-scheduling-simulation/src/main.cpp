#include <iostream>
#include "../include/clock.h"
#include "../include/types.h"
#include "../include/escalonator.h"
#include "../include/usecase.h"
using namespace std;

void processSchedulerEmpty(Escalonator &scheduler, UseCase &hospitalHZ, Clock &simulationClock)
{
    for (int i = 0; i < INDEXCAST(QueueType::TOTAL); i++)
    {
        if (hospitalHZ.hasSpaceInProcedure(static_cast<QueueType>(i)) && !hospitalHZ.isEmptyQueue(static_cast<QueueType>(i)))
        {
            for (int j = 0; j < hospitalHZ.getSpaceInProcedure(static_cast<QueueType>(i)); j++)
            {
                scheduler.addEvent(simulationClock.getCurrentTime(), QueueTypeToState(static_cast<QueueType>(i)), nullptr);
            }
        }
    }
}
int main(int argc, char *argv[])
{
    // if (argc < 2) {
    //     std::cout << "Usage: " << argv[0] << " <csv-file>" << std::endl;
    //     return 1;
    // }

    UseCase hospitalHZ;

    // std::string filePath = argv[1];
    // hospitalHZ.init(filePath);

    // Load the use case data
    hospitalHZ.init("/Users/gil/Code/faculdade/ED/TP2/hospital-scheduling-simulation/data/teste.csv");

    Escalonator scheduler;
    Patient *nextPatient = hospitalHZ.getArrivalPatient();
    if (nextPatient == nullptr)
    {
        // std:://cout << "No patients have arrived" << std::endl;
        return 0;
    }

    Clock simulationClock(nextPatient->getYear(), nextPatient->getMonth(), nextPatient->getDay(), nextPatient->getHour());
    scheduler.addEvent(0, State::NotArrived, nextPatient);
    nextPatient = hospitalHZ.getArrivalPatient();
    std::cout << nextPatient->getId() << std::endl;
    while (nextPatient != nullptr)
    {
        int timeDifference = simulationClock.getTimeDifference(nextPatient->getYear(), nextPatient->getMonth(), nextPatient->getDay(), nextPatient->getHour());
        scheduler.addEvent(timeDifference, State::NotArrived, nextPatient);
        nextPatient->setEnteredQueue(timeDifference);
        std::cout << nextPatient->getId() << std::endl;
        nextPatient = hospitalHZ.getArrivalPatient();
    }

    // Schedule initial patient arrival events
    // This would typically involve creating patient events and adding them to the event list
    // For example:
    // Escalonator.addEvent(new PatientArrivalEvent(simulationClock.getCurrentTime(), patient));

    // Main simulation loop

    while (!scheduler.isEmpty() || !hospitalHZ.isAllEmpty())
    {
        bool schedulerEmpty = scheduler.isEmpty();

        if (schedulerEmpty)
        {
            //std::cout << "Scheduler is empty" << std::endl;
            //std::cout << hospitalHZ.getArrivalPatient() << std::endl;
            processSchedulerEmpty(scheduler, hospitalHZ, simulationClock);
        }

        Event *event = scheduler.getNextEvent();
        if (!event)
            continue;

        // Advance the clock to the event's time
        simulationClock.advanceTime(event->time);

        // Process the event
        tuple<Event *, Event *> * nextEvent = hospitalHZ.processEvent(event);
        if (nextEvent != nullptr)
        {
        if (get<0>(*nextEvent) != nullptr)
        {
            scheduler.addEvent(get<0>(*nextEvent)->time, get<0>(*nextEvent)->code, get<0>(*nextEvent)->patient);
        }
        }
        scheduler.checkQueues(&hospitalHZ, simulationClock.getCurrentTime());

        // Clean up the event pointer

        delete event;
    }
    //std::cout << "Results:" << std::endl;
    hospitalHZ.printResults();
    return 0;
}