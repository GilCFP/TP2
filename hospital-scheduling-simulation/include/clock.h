#ifndef CLOCK_H
#define CLOCK_H
class Clock {
public:
    Clock(int year, int month, int day, double hour);

    // Get the current simulated time
    double getCurrentTime() const;
    double getTimeDifference(int year, int month, int day, double hour);
    int startYear, startMonth, startDay;
    double startHour;
    // Advance the clock to the next event time
    void advanceTime(double timeIncrement);

private:
    double currentTime; // Current time in the simulation
};
#endif