#include "../include/patient.h"

Patient::Patient(int id, int discharged, int year, int month, int day, int hour, int urgency, int hospitalMeasures,
                 int labExams, int imagingExams, int consumables)
     : id(id), discharged(discharged), year(year), month(month), day(day), hour(hour),
     urgency(static_cast<Urgency>(urgency)), hospitalMeasures(hospitalMeasures),
     labExams(labExams), imagingExams(imagingExams), consumables(consumables),
     state(State::NotArrived), idleTime(0), timeInTreatment(0) {}

void Patient::discharge(double simulationTime)
{
    stateTimes[INDEXCAST(state)].exitTime = timeInTreatment;
    state = State::HospitalDischarge;
    discharged = 1;
    stateTimes[INDEXCAST(state)].entryTime = simulationTime;
    
}

void Patient::incrementHospitalMeasures()
{
    hospitalMeasures++;
}

void Patient::incrementLabExams()
{
    labExams++;
}

void Patient::incrementImagingExams()
{
    imagingExams++;
}

void Patient::incrementConsumables()
{
    consumables++;
}

void Patient::changeUrgency(Urgency newUrgency)
{
    urgency = newUrgency;
    return;
}

void Patient::changeState(State newState, int simulationTime)
{

    if (static_cast<int>(newState) <= static_cast<int>(state))
    {
        throw std::logic_error("Invalid state transition: new state must be ahead of the current state");
    }

    int currentStateIndex = static_cast<int>(state) - 1;

    // Register the exit time of the current state
    if (currentStateIndex >= 0 && currentStateIndex < 13)
    {
        stateTimes[currentStateIndex].exitTime = simulationTime;
    }

    // Update the current state and entry time
    state = newState;
    currentStateIndex = static_cast<int>(newState) - 1;
    if (currentStateIndex >= 0 && currentStateIndex < 13)
    {
        stateTimes[currentStateIndex].entryTime = simulationTime;
    }
    return;
}

void Patient::goToNextState(double simulationTime)
{
    int currentStateIndex = INDEXCAST(state) - 1;

    // Ensure the current state is not the last one
    if (state == State::HospitalDischarge)
    {
        throw std::logic_error("Cannot transition from HospitalDischarge state");
    }

    // Update the exit time for the current state
    if (currentStateIndex >= 0 && currentStateIndex < 13)
    {
        stateTimes[currentStateIndex].exitTime = simulationTime;
    }

    // Move to the next state
    state = static_cast<State>(static_cast<int>(state) + 1);
    int nextStateIndex = static_cast<int>(state) - 1;

    // Update the entry time for the next state
    if (nextStateIndex >= 0 && nextStateIndex < 13)
    {
        stateTimes[nextStateIndex].entryTime = simulationTime;
    }
}

int Patient::getId() const
{
    return id;
}

int Patient::getYear() const
{
    return year;
}

int Patient::getMonth() const
{
    return month;
}

int Patient::getDay() const
{
    return day;
}

int Patient::getHour() const
{
    return hour;
}

int Patient::getHospitalMeasures() const
{
    return hospitalMeasures;
}

int Patient::getLabExams() const
{
    return labExams;
}

int Patient::getImagingExams() const
{
    return imagingExams;
}

int Patient::getConsumables() const
{
    return consumables;
}

Urgency Patient::getUrgency() const
{
    return urgency;
}

State Patient::getState() const
{
    return state;
}

double Patient::getIdleTime() const
{
    return idleTime;
}

double Patient::getTimeInTreatment() const
{
    return timeInTreatment;
}

int Patient::getStatus() const
{
    return discharged;
}

void Patient::increaseIdleTime(double simulationTime)
{
    idleTime += simulationTime - enteredQueue;
}

void Patient::increaseTimeInTreatment(double timeInTreatment)
{
    this->timeInTreatment += timeInTreatment;
}

int Patient::getProcedures(State state){
    switch (state)
    {
    case State::OnHospitalMeasures:
        return hospitalMeasures;
        break;
    case State::OnLabExams:
        return labExams;
        break;
    case State::OnImagingExams:
        return imagingExams;
        break;
    case State::OnConsumables:
        return consumables;
        break;
    case State::OnAttendance:
    case State::OnTriage:
        return 1;
        break;
    
    default:
        return 1;
    }
}

int Patient::getProcedures(){
    return getProcedures(state);
}

double Patient::getEnteredQueue() const
{
    return enteredQueue;
}

void Patient::setEnteredQueue(double enteredQueue)
{
    this->enteredQueue = enteredQueue;
}

void Patient::printResults() const {
    // 1) Convert original arrival data into a std::tm, then to time_t
    std::tm arrivalTimeStruct = {};
    arrivalTimeStruct.tm_year = year - 1900;
    arrivalTimeStruct.tm_mon  = month - 1;
    arrivalTimeStruct.tm_mday = day;
    arrivalTimeStruct.tm_hour = hour;
    arrivalTimeStruct.tm_min  = 0;
    arrivalTimeStruct.tm_sec  = 0;
    arrivalTimeStruct.tm_isdst = -1;   // Let mktime() figure out DST

    // Normalize arrivalTimeStruct (fill in tm_wday, tm_yday, etc.)
    std::time_t arrivalEpoch = std::mktime(&arrivalTimeStruct);

    // 2) Calculate total time in hours, convert to seconds, add to arrivalEpoch
    double totalTime = idleTime + timeInTreatment;
    int hoursPart = static_cast<int>(totalTime);
    int minutesPart = static_cast<int>((totalTime - hoursPart) * 60);

    std::time_t dispatchedEpoch = arrivalEpoch + (hoursPart * 3600) + (minutesPart * 60);

    // 3) Convert both arrival and dispatched to localtime for printing
    std::tm arrivalLocal = *std::localtime(&arrivalEpoch);
    std::tm dispatchedLocal = *std::localtime(&dispatchedEpoch);

    // 4) Format and print
    char arrivalBuffer[80];
    char dispatchedBuffer[80];
    std::strftime(arrivalBuffer, sizeof(arrivalBuffer), "%a %b %e %H:%M:%S %Y", &arrivalLocal);
    std::strftime(dispatchedBuffer, sizeof(dispatchedBuffer), "%a %b %e %H:%M:%S %Y", &dispatchedLocal);

    std::cout << id << " "
              << arrivalBuffer << " " << dispatchedBuffer << " "
              << std::fixed << std::setprecision(2) << totalTime << " "
              << std::fixed << std::setprecision(2) << timeInTreatment << " "
              << std::fixed << std::setprecision(2) << idleTime
              << std::endl;
}