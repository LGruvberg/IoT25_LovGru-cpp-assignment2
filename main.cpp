/*  LOOK HERE
Compile using the following commands
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
        interface();
        std::cin >> choice;
        

        switch (choice) {
        case 1: {
            int limit;
            std::cout << "How many values would you like to add?\n\n\tAnswer:\t";
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
        default: 
            std::cout << "Invalid option.\n"; break;
            continue;
        }
    } while (choice != 6);

    return 0;
}
void interface() {
    std::cout << "\n1. Add values\n2. Statistics\n3. Search\n4. Sort\n5. Save to .csv\n6. EXIT\n\n\tAnswer:\t";
}
