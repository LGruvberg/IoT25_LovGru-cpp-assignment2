#include <iostream>
#include "DataManager.h"

void interface() {
    std::cout << "\n1. L�gg till m�tv�rden\n2. Statistik\n3. S�k\n4. Sortera\n5. Avsluta\nSvar: ";
}

int main() {
    DataManager dm;
    int choice = 0;

    do {
        interface();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int limit;
            std::cout << "Hur m�nga v�rden? ";
            std::cin >> limit;
            dm.setValueAmountLimit(limit);
            dm.dataEntry();
            break;
        }
        case 2: dm.statFunc(); break;
        case 3: dm.searchFunc(); break;
        case 4: dm.sortFunc(); break;
        case 5: std::cout << "Avslutar...\n"; break;
        default: std::cout << "Fel val.\n"; break;
        }
    } while (choice != 5);

    return 0;
}
