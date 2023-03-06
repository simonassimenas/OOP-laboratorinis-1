#include "mylib.h"
#include "addFunctions.h"

void output_template() {
    cout << setw(15) << left << "\nVardas" << setw(20) << left << "Pavarde" <<
    setw(34) << left << "Galutinis(Vid.) / Galutinis (Med.)\n";
    cout << "---------------------------------------------------------------------\n";
}

void spausd(studentas &temp, string outputPasirinkimas) {
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;

    if(outputPasirinkimas == "a" || outputPasirinkimas == "A") {
        cout << setw(4) << setprecision(3) << temp.galutinisVid << "              "
        << setw(4) << setprecision(3) << temp.galutinisMed << "\n";
    }
    else if (outputPasirinkimas == "v" || outputPasirinkimas == "V") {
        cout << setw(4) << setprecision(3) << temp.galutinisVid << "\n";
    }
    else
        cout << "                   " << setw(4) << setprecision(3) << temp.galutinisMed << "\n";
}


bool getBoolInput() {
    bool input;

    while(!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
    }
    return input;
}

bool isNumber(const string& str) {
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

string getChoiceInput() {
    string input;

    while (true) {
        cin >> input;
        if (!isNumber(input) 
        && (input == "v" || input == "V" 
        || input == "m" || input == "M" 
        || input == "a" || input == "A")) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Netinkama ivestis. Iveskite v, m arba a:\n";
    }
    return input;
}

string getStringInput() {
    string input;

    while (true) {
        cin >> input;
        if (!isNumber(input)) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Netinkama ivestis. Iveskite dar karta:\n";
    }
    return input;
}

int gradeInput() {
    int input;
    cin >> input;

    if(input == 33) {
        return input;
    }
    while (true) {
        try {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Netinkama ivestis.");
            }
            if (input < 0 || input > 10) {
                throw out_of_range("Iveskite skaiciu esanti 10-baleje sistemoje.");
            }
            break;
        } 
        catch (const exception& e) {
            cout << e.what() << "\n";
            cout << "Iveskite tinkama skaiciu:\n";
            cin >> input;
        }
    }
    return input;
}

int autoGradeInput() {
    int input;

    while(true) {
        try {
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Netinkama ivestis.");
            }
            if (input < 1) {
                throw out_of_range("Namu darbu skaicius turetu buti naturalusis.");
            }
            break;
        }
        catch (const exception& e) {
            cout << e.what() << "\n";
            cout << "Iveskite tinkama skaiciu:\n";
        }
    }
    return input;
}