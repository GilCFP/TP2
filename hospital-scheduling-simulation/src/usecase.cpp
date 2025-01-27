#include "../include/usecase.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

UseCase::UseCase()
{
    initializeQueues();
}

UseCase::~UseCase()
{
    cleanupQueues();
}

Patient *UseCase::getArrivalPatient()
{
    try
    {
        return arrivalQueue->Dequeue();
    }
    catch (std::out_of_range e)
    {
        return nullptr;
    }
}

void UseCase::initializeQueues()
{
    arrivalQueue = new Queue();
    for (size_t i = 0; i < INDEXCAST(QueueType::TOTAL); ++i)
    {
        for (size_t j = 0; j < INDEXCAST(Urgency::TOTAL); ++j)
        {
            queues[i][j] = new Queue();
        }
    }
}

void UseCase::cleanupQueues()
{
    delete arrivalQueue;
    for (size_t i = 0; i < INDEXCAST(QueueType::TOTAL); ++i)
    {
        for (size_t j = 0; j < INDEXCAST(Urgency::TOTAL); ++j)
        {
            delete queues[i][j];
        }
    }
}

bool UseCase::isAllEmpty() const
{
    if (!arrivalQueue->IsEmpty())
    {
        return false;
    }
    for (size_t i = 0; i < INDEXCAST(QueueType::TOTAL); ++i)
    {
        for (size_t j = 0; j < INDEXCAST(Urgency::TOTAL); ++j)
        {
            if (!queues[i][j]->IsEmpty())
            {
                return false;
            }
        }
    }
    return true;
}

void UseCase::init(const std::string &filePath)
{
    extractData(filePath);

    for (size_t i = 0; i < INDEXCAST(QueueType::TOTAL); ++i)
    {
        procedures[i] = new Procedure(capacities[i], times[i]);
    }
}

std::tuple<Event*, Event*> * UseCase::processEvent(Event *event)
{
    int code = INDEXCAST(event->code);
    int queueIndex = INDEXCAST(StateToQueueType(event->code));

    Patient *patient;
    Event *newEvent;
    double timeInProcedure;

    switch (event->code)
    {
    case State::WaitingForTriage:
    case State::WaitingForAttendance:
    case State::WaitingForHospitalMeasures:
    case State::WaitingForLabExams:
    case State::WaitingForImagingExams:
    case State::WaitingForConsumables:

        patient = getNextPatient(static_cast<QueueType>(queueIndex));
        if (patient == nullptr)
        {
            //cout << "No more patients in queue" << QueueTypetoString(static_cast<QueueType>(queueIndex)) << endl;
            procedures[queueIndex]->endProcedure();
            return nullptr;
        }

        patient->goToNextState(event->time);

        timeInProcedure = procedures[queueIndex]->getAverageTime() * patient->getProcedures();
        patient->increaseTimeInTreatment(timeInProcedure);
        patient->increaseIdleTime(event->time);
        newEvent = new Event{event->time + timeInProcedure, static_cast<State>(code + 1), patient};

        //cout << "Patient " << patient->getId() << " leaved queue " << StateToString(event->code) << " at " << event->time << endl;

        return new tuple<Event*, Event*>{newEvent, nullptr};

    case State::OnAttendance:
        if (event->patient->getStatus() == 1)
        {
            patient = event->patient;
            procedures[queueIndex]->endProcedure();
            event->patient->discharge(event->time);
            //cout << "Patient " << patient->getId() << " discharged immediatly" << " at: "<< event->time<<endl;
            //timeInProcedure = procedures[queueIndex]->getAverageTime() * patient->getProcedures();

            //patient->increaseTimeInTreatment(timeInProcedure);
            return nullptr;
        }
    case State::OnTriage:
    case State::OnHospitalMeasures:
    case State::OnLabExams:
    case State::OnConsumables:
    case State::OnImagingExams:

        //cout << "Patient " << event->patient->getId() << " realized procedure " << StateToString(event->code) << " at " << event->time << endl;
        patient = event->patient;

        patient->goToNextState(event->time);

        procedures[queueIndex]->endProcedure();
        newEvent = new Event{event->time, static_cast<State>(code - 1), nullptr};

        if (event->code == State::OnConsumables)
        {
            patient->discharge(event->time);
            return nullptr;
            //cout << "Patient " << patient->getId() << " discharged" << endl;
        }
        else
        {
            queues[queueIndex + 1][INDEXCAST(patient->getUrgency())]->Enqueue(patient);
            patient->setEnteredQueue(event->time);
        }
        return nullptr;

    case State::NotArrived:

        patient = event->patient;
        //cout << "Patient " << patient->getId() << " arrived at " << event->time << endl;
        patient->goToNextState(event->time);
        patient->setEnteredQueue(event->time);
        //cout << "Patient " << event->patient->getId() << " realized procedure " << StateToString(event->code) << " at " << event->time << endl;
        queues[INDEXCAST(QueueType::Triage)][INDEXCAST(Urgency::Red)]->Enqueue(event->patient);
        return nullptr;


    default:
        break;
    }
    //cout << INDEXCAST(event->code) << endl;
    throw std::runtime_error("Invalid event code");
}

Patient *UseCase::getNextPatient(QueueType queueType)
{

    for (int j = INDEXCAST(Urgency::TOTAL) - 1; j >= 0; j--)
    {
        if (!queues[INDEXCAST(queueType)][j]->IsEmpty())
        {
            return queues[INDEXCAST(queueType)][j]->Dequeue();
        }
    }

    return nullptr;
}

void UseCase::extractData(const std::string &filePath)
{

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file" + filePath);
    }

    std::string line;

    for (size_t i = 1; i < INDEXCAST(QueueType::TOTAL); ++i)
    {
        std::getline(file, line, ' ');
        times[i] = std::stof(line);
        std::getline(file, line, '\n');
        capacities[i] = std::stoi(line);
    }

    std::getline(file, line, '\n');
    numberOfPatients = std::stoi(line);

    patients = new Patient *[numberOfPatients];

    for (int i = 0; i < numberOfPatients; i++)
    {
        std::getline(file, line, ' ');
        int id = std::stoi(line);
        std::getline(file, line, ' ');
        int alta = std::stoi(line);
        std::getline(file, line, ' ');
        int ano = std::stoi(line);
        std::getline(file, line, ' ');
        int mes = std::stoi(line);
        std::getline(file, line, ' ');
        int dia = std::stoi(line);
        std::getline(file, line, ' ');
        int hora = std::stoi(line);
        std::getline(file, line, ' ');
        int grau = std::stoi(line);
        std::getline(file, line, ' ');
        int mh = std::stoi(line);
        std::getline(file, line, ' ');
        int tl = std::stoi(line);
        std::getline(file, line, ' ');
        int ei = std::stoi(line);
        std::getline(file, line, '\n');
        int im = std::stoi(line);
        Patient *patient = new Patient(id, alta, ano, mes, dia, hora, grau, mh, tl, ei, im);
        patients[i] = patient;
        arrivalQueue->Enqueue(patient);
    }
}

bool UseCase::isEmptyQueue(QueueType queueType)
{
    for (size_t i = 0; i < INDEXCAST(Urgency::TOTAL); ++i)
    {
        if (!queues[INDEXCAST(queueType)][i]->IsEmpty())
        {
            return false;
        }
    }
    return true;
}

bool UseCase::isEmptyProcedure(QueueType queueType)
{
    return procedures[INDEXCAST(queueType)]->getAvaliableUnits() == 0;
}

bool UseCase::hasSpaceInProcedure(QueueType queueType)
{
    return procedures[INDEXCAST(queueType)]->getAvaliableUnits() > 0;
}

int UseCase::getAttendanceCapacity()
{
    return capacities[INDEXCAST(QueueType::Attendance)];
}

int UseCase::getSpaceInProcedure(QueueType queueType)
{
    return procedures[INDEXCAST(queueType)]->getAvaliableUnits();
}

void UseCase::printPatientsAdresses(){
    for (int i = 0; i < numberOfPatients; i++)
    {
        //cout << "Patient " << patients[i]->getId() << " Address: " << patients[i] << endl;
    }
}


void UseCase::printResults()
{
    for (int i = 0; i < numberOfPatients; i++)
    {
        patients[i]->printResults();
    }
}
