#pragma once
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

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

private:
    //void interface() const;
    void badInput() const;
    double sumFunc() const;
    double meanFunc() const;
    double varianceFunc() const;
};

#endif
