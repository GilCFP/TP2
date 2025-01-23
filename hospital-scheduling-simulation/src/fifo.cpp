#include "../include/fifo.h"
#include <stdexcept>

Fifo::~Fifo() {
    while (!IsEmpty()) {
        Dequeue();
    }
}

void Fifo::Enqueue(Patient* p) {
    Node* newNode = new Node(p);
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

Patient* Fifo::Dequeue() {
    if (IsEmpty()) {
        throw std::out_of_range("Fifo is empty");
    }
    Node* temp = head;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    Patient* result = temp->ptr;
    delete temp;
    return result;
}

bool Fifo::IsEmpty() const {
    return head == nullptr;
}