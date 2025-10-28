#pragma once
#include <vector>

class DataManager {
private:
    std::vector<double> data;
    int valueAmountLimit;
    
    public:
    DataManager();
    void setValueAmountLimit(int limit);
    void dataEntry();
    void rndFunc();
    void statFunc() const;
    void searchFunc() const;
    void sortFunc();
    void convertIntoFile();
    void interface();
    double bmiCalc() const;
    
    private:
    //void interface() const;
    void badInput() const;
    double sumFunc() const;
    double meanFunc() const;
    double varianceFunc() const;
};
