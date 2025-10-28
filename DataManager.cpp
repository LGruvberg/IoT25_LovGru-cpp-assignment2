#include "DataManager.hpp"
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <random>

#include <filesystem>
#include <chrono>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

DataManager::DataManager() : valueAmountLimit(0) {}

void DataManager::interface() {
    std::cout 
        << "\n1. Add values" 
        << "\n2. Statistics" 
        << "\n3. Search" 
        << "\n4. Sort" 
        << "\n5. Save to .csv" 
        << "\n6. EXIT" 
        << "\n9. [BONUS] BMI calculator\n\n\tChoice:\t";
}

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

double DataManager::bmiCalc() const {
    double 
        height_cm, 
        weight_kg, 
        height_m, bmi;
    
    std::cout << "\nTime to calculate BMI!\n";
    std::cout << "\nHow tall are you? (cm)\nAnswer:\t";
    std::cin >> height_cm;
    std::cout << "\nHow much do you weigh? (kg)\nAnswer:\t";
    std::cin >> weight_kg;

    height_m = height_cm / 100.0;  // Convert cm to meters
    bmi = weight_kg / (height_m * height_m);

    std::cout << "Your BMI is: " << bmi << std::endl;

    if (bmi < 18.5)
        std::cout << "You are what the doctors call Underweight" << std::endl;
    else if (bmi < 24.9)
        std::cout << "You are what the doctors call Normal weight" << std::endl;
    else if (bmi < 29.9)
        std::cout << "You are what the doctors call Overweight" << std::endl;
    else
        std::cout << "You are what the doctors call Obesity" << std::endl;
        
    return bmi;
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
    double sum = sumFunc();
    double mean = meanFunc();
    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());
    double variance = varianceFunc();
    double stdDevi = sqrt(variance);
    
    std::cout 
        << "Sum:\n\t"     << sum << "\n"
        << "Mean:\n\t"    << mean << "\n"
        << "Lowest:\n\t"  << minVal << "\n"
        << "Highest:\n\t" << maxVal << "\n"
        << "Variance:\n\t"<< variance << "\n"
        << "Standard Deviation:\n\t" << stdDevi << "\n";
}

void DataManager::searchFunc() const {
    if (data.empty()) {
        std::cout << "No searchable values (add values first through menu option '1'!)\n\n";
        return;
    }
    std::cout << "Search value: ";
    double s;
    std::cin >> s;

    bool exists = false;
    constexpr double tolerance = 0.01;   // Search precision (1/100)

    std::cout << "\nResult:\n";
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (std::abs(data[i] - s) <= tolerance) {
            std::cout 
                << "Found value '"  << s 
                << "' at position " << i + 1 << "\n";
            exists = true;
            return;
        }
    }
    if (!exists) {
        std::cout << s << " could not be found.\n\n";
    }
}

void DataManager::sortFunc() {
    if (data.empty()) {
        std::cout << "There's nothing to sort (hint: menu option '1'!)\n\n";
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
        return;
    }
    std::cout << "Sorted list:\n";
    for (double v : data) {
        std::cout << "\t" << v;
        std::cout << "\n";
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

void DataManager::convertIntoFile() {
    if (data.empty()) {
        std::cout << "No data to write! Add values first.\n";
        return;
    }
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&t);
    
    //  FOLDER NAME (Statistics_YYYY_MM)
    std::ostringstream folder_ss;
    folder_ss << "Statistics_" << std::put_time(&local_tm, "%Y_%m");
    fs::path folder_path = fs::current_path() / folder_ss.str();
    fs::create_directories(folder_path);
    
    //  FILE NAME   (Statdata_YYYY_MM_DD_HHhSSs.csv)
    std::ostringstream file_ss;
    file_ss << "Statdata_" << std::put_time(&local_tm, "%Y_%m_%d_%Hh%Mm%Ss") << ".csv";
    fs::path file_path = folder_path / file_ss.str();

    std::ofstream outputFile(file_path);
    if (!outputFile) {
        std::cerr << "Failed to create file: " << file_path << ".\n";
        return;
    }

    //  Write data
    outputFile << "Index\t|\tValue\n";  // Column headers
    for (std::size_t i = 0; i < data.size(); ++i) {
        outputFile << "\t" << (i + 1) << "\t|\t" << data[i] << "\n";
    }

    // outputFile << statFunc;   
    double sum = sumFunc();
    double mean = meanFunc();
    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());
    double variance = varianceFunc();
    double stdDevi = sqrt(variance);
    double bmi = bmi;
    
    outputFile << "\n.:STATISTICS:.\n";
    outputFile << "METRIC\t\t|\tVALUE\n";
    outputFile << "Sum      \t|\t"  << sum << "\n";
    outputFile << "Mean     \t|\t"  << mean << "\n";
    outputFile << "Lowest   \t|\t"  << minVal << "\n";
    outputFile << "Highest  \t|\t"  << maxVal << "\n";
    outputFile << "Variance \t|\t"  << variance << "\n";
    outputFile << "StdDevi  \t|\t"  << stdDevi << "\n";
    outputFile << "BMI  \t|\t"  << bmiCalc << "\n"; // Print this in convert file?

    outputFile.close();
    std::cout << "New .csv file located at: " << file_path << ".\n";
}
