#include "../include/escalonator.h"
#include <stdexcept>

Escalonator::Escalonator(){}

Escalonator::~Escalonator() {}


void Escalonator::addEvent(double time, State code, Patient* patient) {
    Event event = {time, code, patient};
    eventQueue.addEvent(event);
    
}

Event* Escalonator::getNextEvent() {
    return eventQueue.getNextEvent();
}

bool Escalonator::isEmpty() const {
    return eventQueue.isEmpty();
}

void Escalonator::checkQueues(UseCase* useCase, double simulationTime) {
    for (size_t i = 0; i < INDEXCAST(QueueType::TOTAL); ++i) {
        auto queueType = static_cast<QueueType>(i);

        if (!useCase->isEmptyQueue(queueType) && useCase->hasSpaceInProcedure(queueType)) {
            addEvent(simulationTime, QueueTypeToState(queueType), nullptr);
            useCase->procedures[i]->startProcedure();
        }
    }
}