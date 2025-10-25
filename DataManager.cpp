#include "DataManager.h"
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <random>

DataManager::DataManager() : valueAmountLimit(0) {}

void DataManager::setValueAmountLimit(int limit) {
    valueAmountLimit = limit;
}

void DataManager::badInput() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input, please try again...\n";
}

void DataManager::dataEntry() {
    std::cout << "\n\t1. Manual input\n\t2. Generate random\n\n\tAnswer:\t";
    int choice;
    std::cin >> choice;

    if (choice == 2) {
        rndFunc();
        return;
    }
    int count = 1;
    while (count <= valueAmountLimit) {
        std::cout << "Value " << count << ": ";
        std::string input;
        std::cin >> input;

        if (input == "q") break;

        try {
            double value = std::stod(input);
            data.push_back(value);
            count++;
        }
        catch (...) {
            badInput();
        }
    }
}

void DataManager::rndFunc() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 101.0);

    for (int i = 0; i < valueAmountLimit; ++i) {
        double randValue = dist(gen);
        data.push_back(randValue);
        std::cout << "Random " << i + 1 << ": " << randValue << "\n";
    }
}

void DataManager::statFunc() const {
    if (data.empty()) {
        std::cout << "No data available for statistics (add values first through menu option '1'!)\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sum: " << sumFunc() << "\n";
    std::cout << "Mean: " << meanFunc() << "\n";
    std::cout << "Variance: " << varianceFunc() << "\n";
}

void DataManager::searchFunc() const {
    if (data.empty()) {
        std::cout << "No searchable values (add values first through menu option '1'!)\n\n";
        return;
    }
    std::cout << "Search value: ";
    double s;
    std::cin >> s;

    for (size_t i = 0; i < data.size(); ++i) {
        if (std::abs(data[i] - s) < 1e-9) {
            std::cout << "Found '" << s << "' at position " << i + 1 << "\n";
            return;
        }
    }
    std::cout << "The position you searched for seems empty.\n\n";
}

void DataManager::sortFunc() {
    if (data.empty()) {
        std::cout << "There's nothing to sort (add values first through menu option '1'!)\n\n";
        return;
    }

    std::cout << "1. Ascending\n2. Descending\nAnswer: ";
    int sortChoice;
    std::cin >> sortChoice;

    if (sortChoice == 1) {
        std::sort(data.begin(), data.end());
    }
    else if (sortChoice == 2) {
        std::sort(data.rbegin(), data.rend());
    }
    else {
        badInput();
    }
}

double DataManager::sumFunc() const {
    return std::accumulate(data.begin(), data.end(), 0.0);
}

double DataManager::meanFunc() const {
    return sumFunc() / data.size();
}

double DataManager::varianceFunc() const {
    if (data.size() < 2) return 0.0;

    double m = meanFunc();
    double sum = 0.0;
    for (double v : data) {
        sum += (v - m) * (v - m);
    }
    return sum / (data.size() - 1);
}
