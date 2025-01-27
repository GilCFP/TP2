#ifndef USECASE_H
#define USECASE_H

#include "queue.h"
#include <string>
#include "procedure.h"
#include "event.h"
#include "fifo.h"

class UseCase {
public:
    UseCase();
    ~UseCase();
    void init(const std::string &filePath);
    bool isAllEmpty() const;
    std::tuple<Event*, Event*>* processEvent(Event* event);
    bool isEmptyQueue(QueueType queueType);
    bool isEmptyProcedure(QueueType queueType);
    int getAttendanceCapacity();
    int getSpaceInProcedure(QueueType queueType);
    bool hasSpaceInProcedure(QueueType queueType);
    void printResults();
    Patient* getArrivalPatient();
    Patient* getNextPatient(QueueType queueType);
    void printPatientsAdresses();
    Procedure* procedures[INDEXCAST(QueueType::TOTAL)];
    Queue* arrivalQueue;
    void cleanupQueues();

private:
    Patient** patients;
    void initializeQueues();
    void extractData(const std::string &filePath);
    
    Queue* queues[INDEXCAST(QueueType::TOTAL)][INDEXCAST(Urgency::TOTAL)];

    // Use Case Variables
    float times[INDEXCAST(State::HospitalDischarge)+1];
    float capacities[INDEXCAST(QueueType::TOTAL)];
    int numberOfPatients;
};

#endif // USECASE_H