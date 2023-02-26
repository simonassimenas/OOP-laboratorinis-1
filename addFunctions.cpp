#include "mylib.h"
#include "addFunctions.h"


double skaicVid(vector<int> &paz_vec) {
    double sum = accumulate(paz_vec.begin(),paz_vec.end(), 0);
    return double(sum / paz_vec.size());
}

double skaicMed(vector<int> &paz_vec) {
    sort(paz_vec.begin(), paz_vec.end());

    size_t size = paz_vec.size();

    if (size % 2 == 0) {
      return double((paz_vec[size/2 - 1] + paz_vec[size/2]) / 2);
    }
    else {
      return double(paz_vec[size / 2]);
    }
}

int randomSkaicius() {
    random_device rd;
    mt19937_64 mt(static_cast<long unsigned int> (rd()));
    uniform_int_distribution<int> dist(0, 10);

    return int(dist(mt));
}

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
    while (!cin || input < 0 || input > 10) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite skaiciu 10-baleje sistemoje:\n";
        cin >> input;
    }
    return input;
}

int autoGradeInput() {
    int input;
    cin >> input;

    while(!cin || input<1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite naturaluji skaiciu:\n";
        cin >> input;
    }
    return input;
}