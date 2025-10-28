/*  LOOK HERE
Compile using:
1.  'g++ main.cpp DataManager.cpp -o mainExecutable'
2.  and then '.\mainExecutable'
*/

#include <iostream>
#include "DataManager.hpp"

void interface();

int main() {
    DataManager dm;
    int choice = 0;
    do {
        dm.interface();
        std::cin >> choice;
        

        switch (choice) {
        case 1: {
            int limit;
            std::cout << "How many values would you like to add?\n\n\tChoice:\t";
            std::cin >> limit;
            dm.setValueAmountLimit(limit);
            dm.dataEntry();
            break;
        }
        case 2: std::cout << std::endl; dm.statFunc(); break;
        case 3: dm.searchFunc(); break;
        case 4: dm.sortFunc(); break;
        case 5: dm.convertIntoFile(); break;
        case 6: std::cout << "\nExiting...\n"; break;
        case 9: dm.bmiCalc(); break;
        default: 
            std::cout << "Invalid option.\n"; break;
            continue;
        }
    } while (choice != 6);

    return 0;
}
