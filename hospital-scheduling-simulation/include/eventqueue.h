#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "event.h"

class EventQueue {
public:
    EventQueue();
    ~EventQueue();

    void addEvent(const Event& event);
    Event* getNextEvent();
    bool isEmpty() const;
    int totalevents = 0;

private:
    struct EventNode {
        Event event;
        EventNode* next;
    };

    EventNode* head;
};

#endif // FIFO_H