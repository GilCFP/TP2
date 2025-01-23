#ifndef QUEUE_H
#define QUEUE_H

#include "patient.h"

class Queue {
public:
    Queue();
    Queue(int capacity);
    ~Queue();

    void Enqueue(Patient* patient);
    void printQueue();
    Patient* Dequeue();
    bool IsEmpty() const;
    int Size() const;

private:
    Patient** heap;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();
    bool comparePatients(Patient* p1, Patient* p2);
};

#endif // QUEUE_H