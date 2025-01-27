#ifndef TYPES_H
#define TYPES_H
#include <stdexcept>
#include <string>
#define INDEXCAST(x) static_cast<unsigned int>(x)

enum class State {
    NotArrived = 1,
    WaitingForTriage,
    OnTriage,
    WaitingForAttendance,
    OnAttendance,
    WaitingForHospitalMeasures,
    OnHospitalMeasures,
    WaitingForLabExams,
    OnLabExams,
    WaitingForImagingExams,
    OnImagingExams,
    WaitingForConsumables,
    OnConsumables,
    HospitalDischarge,
    TOTAL
};

enum class Urgency {
    Green,
    Yellow,
    Red,
    TOTAL
};

enum class QueueType
{
    NotArrived,
    Triage,
    Attendance,
    HospitalMeasures,
    LabExams,
    ImagingExams,
    Consumables,
    TOTAL
};

inline QueueType StateToQueueType(State state) {
    switch (state) {
        case State::NotArrived:
            return QueueType::NotArrived;

        case State::WaitingForTriage:
        case State::OnTriage:
            return QueueType::Triage;

        case State::WaitingForAttendance:
        case State::OnAttendance:
            return QueueType::Attendance;

        case State::WaitingForHospitalMeasures:
        case State::OnHospitalMeasures:
            return QueueType::HospitalMeasures;

        case State::WaitingForLabExams:
        case State::OnLabExams:
            return QueueType::LabExams;

        case State::WaitingForImagingExams:
        case State::OnImagingExams:
            return QueueType::ImagingExams;

        case State::WaitingForConsumables:
        case State::OnConsumables:
            return QueueType::Consumables;

        default:
            return QueueType::TOTAL;
    }
}

inline State QueueTypeToState(QueueType queueType) {
    switch (queueType) {
        case QueueType::NotArrived:
            return State::NotArrived;

        case QueueType::Triage:
            return State::WaitingForTriage;

        case QueueType::Attendance:
            return State::WaitingForAttendance;

        case QueueType::HospitalMeasures:
            return State::WaitingForHospitalMeasures;

        case QueueType::LabExams:
            return State::WaitingForLabExams;

        case QueueType::ImagingExams:
            return State::WaitingForImagingExams;

        case QueueType::Consumables:
            return State::WaitingForConsumables;
            
        default:
            throw std::invalid_argument("Invalid QueueType");
    }
}
inline std::string StateToString(State state) {
    switch (state) {
        case State::NotArrived:
            return "Not Arrived";

        case State::WaitingForTriage:
            return "Waiting for Triage";

        case State::OnTriage:
            return "On Triage";

        case State::WaitingForAttendance:
            return "Waiting for Attendance";

        case State::OnAttendance:
            return "On Attendance";

        case State::WaitingForHospitalMeasures:
            return "Waiting for Hospital Measures";

        case State::OnHospitalMeasures:
            return "On Hospital Measures";

        case State::WaitingForLabExams:
            return "Waiting for Lab Exams";

        case State::OnLabExams:
            return "On Lab Exams";

        case State::WaitingForImagingExams:
            return "Waiting for Imaging Exams";

        case State::OnImagingExams:
            return "On Imaging Exams";

        case State::WaitingForConsumables:
            return "Waiting for Consumables";

        case State::OnConsumables:
            return "On Consumables";

        case State::HospitalDischarge:
            return "Hospital Discharge";

        default:
            return "Invalid State";
    }
}
inline std::string QueueTypetoString(QueueType queue){
    switch (queue)
    {
    case QueueType::NotArrived:
        return "Not Arrived";
    case QueueType::Triage:
        return "Triage";
    case QueueType::Attendance:
        return "Attendance";
    case QueueType::HospitalMeasures:
        return "Hospital Measures";
    case QueueType::LabExams:
        return "Lab Exams";
    case QueueType::ImagingExams:
        return "Imaging Exams";
    case QueueType::Consumables:
        return "Consumables";
    default:
        return "Invalid Queue";
    }
}

#endif