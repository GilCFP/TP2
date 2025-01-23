#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "types.h"
#include <ctime>
#include <iomanip>
#include <iostream>

struct StateTime {
    double entryTime = -1;
    double exitTime = -1;
};

class Patient {
public:
    Patient(int id, int discharged, int year, int month, int day, int hour, int urgency, int hospitalMeasures, 
            int labExams, int imagingExams, int consumables);

    void discharge(double simulationTime);
    void incrementHospitalMeasures();
    void incrementLabExams();
    void incrementImagingExams();
    void incrementConsumables();
    void increaseIdleTime(double idleTime);
    void increaseTimeInTreatment(double timeInTreatment);
    void changeUrgency(Urgency newUrgency);
    void changeState(State newState, int simulationTime);
    void goToNextState(double simulationTime);
    int getProcedures();
    int getProcedures(State state);


    
    int getId() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getHospitalMeasures() const;
    int getLabExams() const;
    int getImagingExams() const;
    int getConsumables() const;
    Urgency getUrgency() const;
    State getState() const;

    double getIdleTime() const;
    double getTimeInTreatment() const;
    int getStatus() const;
    void printResults() const;
    double getEnteredQueue() const;
    void setEnteredQueue(double enteredQueue);

private:
    double enteredQueue;
    int id;
    int discharged = 0;
    int year, month, day, hour;
    Urgency urgency = Urgency::Green;
    int hospitalMeasures, labExams, imagingExams, consumables;
    State state = State::NotArrived;
    double idleTime;
    double timeInTreatment;
    StateTime stateTimes[INDEXCAST(State::TOTAL)+1]; // Array para armazenar entrada e saída de cada estado
};

#endif