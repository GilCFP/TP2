#include "../include/queue.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Queue::Queue() : capacity(10), size(0) {
    heap = new (std::nothrow) Patient*[capacity];
    if (!heap) {
        throw std::bad_alloc();
    }
}

Queue::Queue(int capacity) : capacity(capacity), size(0) {
    heap = new (std::nothrow) Patient*[capacity];
    if (!heap) {
        throw std::bad_alloc();
    }
}

Queue::~Queue() {
    for (int i = 0; i < size; ++i) {
        delete heap[i];
    }
    delete[] heap;
    heap = nullptr;
}

void Queue::Enqueue(Patient* patient) {
    if (size == capacity) {
        resize();
    }
    heap[size] = patient;
    heapifyUp(size);
    size++;
}

Patient* Queue::Dequeue() {
    if (IsEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    Patient* patient = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return patient;
}

bool Queue::IsEmpty() const {
    return size == 0;
}

int Queue::Size() const {
    return size;
}

void Queue::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (comparePatients(heap[index], heap[parentIndex])) {
            break;
        }
        std::swap(heap[index], heap[parentIndex]);
        index = parentIndex;
    }
}

void Queue::heapifyDown(int index) {
    while (2 * index + 1 < size) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestIndex = index;

        if (leftChildIndex < size && !comparePatients(heap[leftChildIndex], heap[smallestIndex])) {
            smallestIndex = leftChildIndex;
        }
        if (rightChildIndex < size && !comparePatients(heap[rightChildIndex], heap[smallestIndex])) {
            smallestIndex = rightChildIndex;
        }
        if (smallestIndex == index) {
            break;
        }
        std::swap(heap[index], heap[smallestIndex]);
        index = smallestIndex;
    }
}

void Queue::resize() {
    capacity *= 2;
    Patient** newHeap = new Patient*[capacity];
    std::copy(heap, heap + size, newHeap);
    delete[] heap;
    heap = newHeap;
}

bool Queue::comparePatients(Patient* p1, Patient* p2) {
    return std::make_tuple(p1->getYear(), p1->getMonth(), p1->getDay(), p1->getHour(), p1->getId()) >
           std::make_tuple(p2->getYear(), p2->getMonth(), p2->getDay(), p2->getHour(), p2->getId());
}

void Queue::printQueue() {
    for (int i = 0; i < size; ++i) {
        //std:://cout << INDEXCAST(heap[i]->getId()) << " ";
    }
    //std:://cout << std::endl;
}