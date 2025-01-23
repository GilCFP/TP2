#include "../include/eventqueue.h"
#include <stdexcept>

EventQueue::EventQueue() : head(nullptr) {}

EventQueue::~EventQueue() {
    while (head != nullptr) {
        EventNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void EventQueue::addEvent(const Event& event) {
    EventNode* newNode = new EventNode{event, nullptr};
    if (head == nullptr || head->event.time > event.time) {
        newNode->next = head;
        head = newNode;
    } else {
        EventNode* current = head;
        while (current->next != nullptr && current->next->event.time <= event.time) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    totalevents++;
}

Event* EventQueue::getNextEvent() {
    if (head == nullptr)return nullptr;
    EventNode* temp = head;
    head = head->next;
    Event* event = new Event(temp->event);
    delete temp;
    totalevents--;
    return event;
}

bool EventQueue::isEmpty() const {
    return head == nullptr;
}