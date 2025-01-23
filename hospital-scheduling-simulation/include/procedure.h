
class Procedure
{

public:
    Procedure(int units, double averageTime);

    int getAvaliableUnits() const;
    int getUnits() const;
    double getAverageTime() const;
    void startProcedure();
    void endProcedure();
    int getEndTime(int quantity);
    void setUnits(int units);
    void setAverageTime(double averageTime);
    

private:
    int total;
    int available;
    double averageTime;
};