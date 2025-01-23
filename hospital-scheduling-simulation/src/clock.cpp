#include "../include/clock.h"

Clock::Clock(int year, int month, int day, double hour) : startYear(year), startMonth(month), startDay(day), startHour(hour), currentTime(0) {}

double Clock::getCurrentTime() const
{
    return currentTime;
}
void Clock::advanceTime(double newTime)
{
    currentTime = newTime;
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

double Clock::getTimeDifference(int year, int month, int day, double hour)
{
    double hourDiff = 0;
    int yearDiff = year - startYear;
    int monthDiff = (yearDiff * 12) + (month - startMonth);
    int dayDiff = day - startDay;
    hourDiff += dayDiff * 24;
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int i = 0; i < yearDiff; ++i) {
        hourDiff += (isLeapYear(startYear + i) ? 366 : 365) * 24;
    }
    for (int i = 0; i < monthDiff; ++i) {
        int monthIndex = (startMonth + i - 1) % 12;
        hourDiff += daysInMonth[monthIndex] * 24;
    }
    hourDiff += hour - startHour;
        
    return hourDiff;
}
