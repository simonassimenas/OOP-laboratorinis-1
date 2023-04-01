#include "addFunctions.h"

int main() {
    int container;
    bool choice = true;

    while (choice) {
        cout << "Pasirinkite konteinerio tipa:\n" <<
        "   1 - Vector\n" <<
        "   2 - Deque\n" <<
        "   3 - List\n";
        container = threeInput();

        switch (container) {
        case 1:
            cout << "\nPrograma paleidziama...\n";
            system("./vector");
            break;
        case 2:
            cout << "\nPrograma paleidziama...\n";
            system("./deque");
            break;
        case 3:
            cout << "\nPrograma paleidziama...\n";
            system("./list");
            break;
        }

        cout << "\nAr norite isbandyti kita konteinerio tipa? (1 - Taip, 0 - Ne)\n";
        choice = getBoolInput();
        if (choice) {
            system("make cleanres");
        }
    }
}
