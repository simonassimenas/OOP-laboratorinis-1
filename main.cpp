#include "addFunctions.h"

int main() {
    int strategy;
    bool choice = true,
    flag_part = false,
    flag_single = false,
    flag_split = false;

    while (choice) {
        cout << "Pasirinkite strategija:\n" <<
        "   1 - Du nauji konteineraiai\n" <<
        "   2 - Originalus ir naujas konteineris\n" <<
        "   3 - Partition metodas\n";
        strategy = strategyInput();

        switch (strategy) {
        case 1:
            cout << "\nPrograma uzkraunama...\n";
            if (!flag_part)
                system("make split");
            system("./split");
            break;
        case 2:
            cout << "\nPrograma uzkraunama...\n";
            if (!flag_single)
                system("make single");
            system("./single");
            break;
        case 3:
            cout << "\nPrograma uzkraunama...\n";
            if (!flag_split)
                system("make partition");
            system("./partition");
            break;
        }

        cout << "\nAr norite isbandyti dar viena strategija? (1 - Taip, 0 - Ne)\n";
        choice = getBoolInput();
        if (choice) {
            system("make cleanres");
        }
    }
}