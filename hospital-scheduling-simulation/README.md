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

## Usage Instructions
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use the provided Makefile to compile the project:
   ```
   make
   ```
4. Run the simulation:
   ```
   ./hospital-scheduling-simulation
   ```

## Running the Simulation
Upon execution, the simulation will initialize the system, schedule patient arrival events, and process events in chronological order. The results will be displayed, including statistics on patient wait times and resource usage.

## Conclusion
This simulation provides a comprehensive tool for understanding hospital scheduling dynamics, allowing for analysis and optimization of patient flow and resource allocation.