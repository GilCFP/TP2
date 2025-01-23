#ifndef FIFO_H
#define FIFO_H

#include "patient.h"

class Fifo {
public:
    Fifo() : head(nullptr), tail(nullptr) {}
    ~Fifo();

    void Enqueue(Patient* p);
    Patient* Dequeue();
    bool IsEmpty() const;

private:
    struct Node {
        Patient* ptr;
        Node* next;
        Node(Patient* p) : ptr(p), next(nullptr) {}
    };

    Node* head;
    Node* tail;
};

#endif