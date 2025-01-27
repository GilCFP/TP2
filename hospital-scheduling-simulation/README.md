# Hospital Scheduling Simulation

## Overview
The Hospital Scheduling Simulation is a discrete event simulation system designed to manage hospital scheduling from patient triage to discharge. The system efficiently handles patient queues, procedures, and hospital resources, providing insights into patient flow and resource utilization.

## Features
- **Patient Management**: Tracks patient states, treatment history, and statistics such as idle time and time in treatment.
- **Procedure Management**: Models available services with details on execution times and resource units.
- **Queue Management**: Manages waiting lines for procedures with efficient enqueue and dequeue operations.
- **Event Scheduling**: Implements a priority queue using a min-heap to manage and process events in chronological order.
- **Time Control**: Simulates time progression to manage event scheduling and processing.
- **Statistical Analysis**: Calculates and retrieves metrics like average wait time and resource usage.

## Project Structure
```
hospital-scheduling-simulation
├── include
│   ├── patient.h
│   ├── procedure.h
│   ├── queue.h
│   ├── scheduler.h
│   ├── clock.h
│   ├── event_list.h
│   ├── statistics.h
├── src
│   ├── patient.cpp
│   ├── procedure.cpp
│   ├── queue.cpp
│   ├── scheduler.cpp
│   ├── clock.cpp
│   ├── event_list.cpp
│   ├── statistics.cpp
│   ├── main.cpp
├── Makefile
└── README.md
```

## Data Structures Used
1. **Queue (Queue.cpp)**
   Implemented to manage patients waiting for procedures, it uses a priority queue based on a min-heap to optimize the selection of the next patient. The implementation follows abstraction principles, allowing different types of queues to be instantiated depending on the simulation's needs.

2. **Scheduler (Escalonator.cpp)**
   Responsible for managing discrete events, it uses a FIFO to keep events ordered chronologically. The implementation is designed to be extensible, supporting the addition of new event types without altering the base functionality.

3. **Patient (Patient.cpp)**
   Represents the patient's record and current state. It includes attributes such as wait times, treatment times, and how long the patient remained in each state. It is designed to be compatible with the Liskov Substitution Principle, facilitating the substitution or extension of behavior for different types of patients, such as priority or emergency patients.

4. **Procedure (Procedure.cpp)**
   Manages the occupancy and idle times of hospital units. The implementation adheres to the Single Responsibility Principle, separating the logic of resource control and procedure statistics.

5. **Use Case (UseCase.cpp)**
   The UseCase class is the core of the application's business rules, designed to manage and orchestrate the hospital system's simulation logic. It encapsulates the data flow and interaction between patients, queues, and procedures, allowing flexibility and scalability. Key features of this class include:
   - Initialization of queues and reading input data from a file.
   - Management of patients and events, allowing each event to be processed according to the system's dynamic conditions.
   - Modularity, ensuring that business logic is isolated, easily understandable, and extensible.

   Additionally, the UseCase design allows it to be adapted to different applications by modifying the logic in the methods responsible for processing events. For example, different priority criteria or scheduling rules can be implemented without altering other parts of the system. This characteristic is essential for applications that demand flexibility, such as hospital systems with customized requirements or simulations in other domains.

   In summary, the UseCase class is the backbone of the system, combining robustness, scalability, and ease of maintenance in a single module.

## Usage Instructions
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use the provided Makefile to compile the project:
   ```
   make
   ```
4. Run the simulation:
   ```
   ./hospital-scheduling-simulation <filepath>
   ```

## Running the Simulation
Upon execution, the simulation will initialize the system, schedule patient arrival events, and process events in chronological order. The results will be displayed, including statistics on patient wait times and resource usage.

## Conclusion
This simulation provides a comprehensive tool for understanding hospital scheduling dynamics, allowing for analysis and optimization of patient flow and resource allocation. The use of SOLID principles in the design of this system ensures that the code is robust, scalable, and easy to maintain. Each component adheres to principles such as single responsibility, open-closed, and dependency inversion, making the system flexible and adaptable to various requirements without compromising the integrity of the existing codebase. This results in a highly efficient and maintainable code structure, facilitating future enhancements and modifications.