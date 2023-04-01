#include "mylib.h"
#include "addFunctions.h"

int randomSkaicius() {
    random_device rd;
    mt19937_64 mt(static_cast<long unsigned int> (rd()));
    uniform_int_distribution<int> dist(0, 10);

    return int(dist(mt));
}

double skaicVid(vector<int> &paz_vec) {
    double sum = accumulate(paz_vec.begin(),paz_vec.end(), 0);
    return double(sum / paz_vec.size());
}

double skaicVid(deque<int> &paz_vec) {
    double sum = accumulate(paz_vec.begin(),paz_vec.end(), 0);
    return double(sum / paz_vec.size());
}

double skaicVid(list<int> &paz_vec) {
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

double skaicMed(deque<int> &paz_vec) {
    sort(paz_vec.begin(), paz_vec.end());

    size_t size = paz_vec.size();

    if (size % 2 == 0) {
      return double((paz_vec[size/2 - 1] + paz_vec[size/2]) / 2);
    }
    else {
      return double(paz_vec[size / 2]);
    }
}

double skaicMed(list<int>& paz_vec) {
    paz_vec.sort();

    size_t size = paz_vec.size();

    if (size % 2 == 0) {
      return double((*(next(paz_vec.begin(), size/2 - 1)) + *(next(paz_vec.begin(), size/2))) / 2);
    }
    else {
      return double(*(next(paz_vec.begin(), size / 2)));
    }
}

void naudotojoIvestis(vector<studentas_v> &grupe) {
    studentas_v laikinas;
    
    string outputPasirinkimas;
    bool pildyti;
    int talpa = 16;

    grupe.reserve(talpa);

    cout << "Skaiciuosime vidurki(v), mediana(m) ar abu(a)?\n";
    outputPasirinkimas = getChoiceInput();

    cout << "Ar norite pildyti irasa? (1 - Taip, 0 - Ne)\n";
    pildyti = getBoolInput();

    while(pildyti) {
        if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*2);

        pild(laikinas);
        grupe.push_back(laikinas);

        cout << "Ar norite pildyti dar viena irasa? (1 - Taip, 0 - Ne)\n";
        pildyti = getBoolInput();
    }
    grupe.shrink_to_fit();

    output_template();
    for(int i=0; i<grupe.size(); i++) spausd(grupe[i], outputPasirinkimas);
}

void pild(studentas_v &temp) {
    cout << "Iveskite varda:\n";
    temp.vardas = getStringInput();

    cout << "Iveskite pavarde:\n";
    temp.pavarde = getStringInput();

    cout << "Rankinis pazymiu ivedimas(1) arba automatinis generavimas(0)?\n";
    bool rankinis = getBoolInput();

    vector<int> nd_vec;
    int resSpace = 16;
    nd_vec.reserve(resSpace);
    int inputOrNum;
    int egz;

    if(rankinis) {
        cout << "Iveskite pazymius. Tam kad sustabdyti ivedima parasykite 33:\n";
        do {
            inputOrNum = gradeInput();
            if(inputOrNum == 33) break;

            if(nd_vec.size() == nd_vec.capacity()) nd_vec.reserve(resSpace*2);

            nd_vec.push_back(inputOrNum);

        } while(cin.eofbit);

        nd_vec.shrink_to_fit();

        cout << "Iveskite egzamino paz.:\n";
        egz = gradeInput();
    }

    else {
        cout << "Iveskite pazymiu skaiciu (egzamino pazymys neieina i nurodyta skaiciu):\n";
        inputOrNum = autoGradeInput();

        int tempNum;
        for(int i=0; i<inputOrNum; i++) {
            tempNum = randomSkaicius();
            nd_vec.push_back(tempNum); 
        }
        egz = randomSkaicius();
    }

    if (nd_vec.size() != 0) {
        temp.galutinisVid = 0.4 * (skaicVid(nd_vec)) + 0.6 * egz;
        temp.galutinisMed = 0.4 * (skaicMed(nd_vec)) + 0.6 * egz;
    }
    else {
        temp.galutinisVid = 0.6 * egz;
        temp.galutinisMed = 0.6 * egz;
    }

    nd_vec.clear();

    cout << "---Duomenys irasyti---\n";
}

void naudotojoIvestis(deque<studentas_d> &grupe) {
    studentas_d laikinas;
    
    string outputPasirinkimas;
    bool pildyti;

    cout << "Skaiciuosime vidurki(v), mediana(m) ar abu(a)?\n";
    outputPasirinkimas = getChoiceInput();

    cout << "Ar norite pildyti irasa? (1 - Taip, 0 - Ne)\n";
    pildyti = getBoolInput();

    while(pildyti) {
        pild(laikinas);
        grupe.push_back(laikinas);

        cout << "Ar norite pildyti dar viena irasa? (1 - Taip, 0 - Ne)\n";
        pildyti = getBoolInput();
    }
    grupe.shrink_to_fit();

    output_template();
    for(int i=0; i<grupe.size(); i++) spausd(grupe[i], outputPasirinkimas);
}

void pild(studentas_d &temp) {
    cout << "Iveskite varda:\n";
    temp.vardas = getStringInput();

    cout << "Iveskite pavarde:\n";
    temp.pavarde = getStringInput();

    cout << "Rankinis pazymiu ivedimas(1) arba automatinis generavimas(0)?\n";
    bool rankinis = getBoolInput();

    vector<int> nd_vec;
    int resSpace = 16;
    nd_vec.reserve(resSpace);
    int inputOrNum;
    int egz;

    if(rankinis) {
        cout << "Iveskite pazymius. Tam kad sustabdyti ivedima parasykite 33:\n";
        do {
            inputOrNum = gradeInput();
            if(inputOrNum == 33) break;

            if(nd_vec.size() == nd_vec.capacity()) nd_vec.reserve(resSpace*2);

            nd_vec.push_back(inputOrNum);

        } while(cin.eofbit);

        nd_vec.shrink_to_fit();

        cout << "Iveskite egzamino paz.:\n";
        egz = gradeInput();
    }

    else {
        cout << "Iveskite pazymiu skaiciu (egzamino pazymys neieina i nurodyta skaiciu):\n";
        inputOrNum = autoGradeInput();

        int tempNum;
        for(int i=0; i<inputOrNum; i++) {
            tempNum = randomSkaicius();
            nd_vec.push_back(tempNum); 
        }
        egz = randomSkaicius();
    }

    if (nd_vec.size() != 0) {
        temp.galutinisVid = 0.4 * (skaicVid(nd_vec)) + 0.6 * egz;
        temp.galutinisMed = 0.4 * (skaicMed(nd_vec)) + 0.6 * egz;
    }
    else {
        temp.galutinisVid = 0.6 * egz;
        temp.galutinisMed = 0.6 * egz;
    }

    nd_vec.clear();

    cout << "---Duomenys irasyti---\n";
}

void naudotojoIvestis(list<studentas_l> &grupe) {
    studentas_l laikinas;
    
    string outputPasirinkimas;
    bool pildyti;
    int talpa = 16;

    cout << "Skaiciuosime vidurki(v), mediana(m) ar abu(a)?\n";
    outputPasirinkimas = getChoiceInput();

    cout << "Ar norite pildyti irasa? (1 - Taip, 0 - Ne)\n";
    pildyti = getBoolInput();

    while(pildyti) {
        pild(laikinas);
        grupe.push_back(laikinas);

        cout << "Ar norite pildyti dar viena irasa? (1 - Taip, 0 - Ne)\n";
        pildyti = getBoolInput();
    }

    output_template();
    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
    spausd(*it, outputPasirinkimas);
    }
}

void pild(studentas_l &temp) {
    cout << "Iveskite varda:\n";
    temp.vardas = getStringInput();

    cout << "Iveskite pavarde:\n";
    temp.pavarde = getStringInput();

    cout << "Rankinis pazymiu ivedimas(1) arba automatinis generavimas(0)?\n";
    bool rankinis = getBoolInput();

    list<int> nd_vec;
    int resSpace = 16;
    // nd_vec.reserve(resSpace);
    int inputOrNum;
    int egz;

    if(rankinis) {
        cout << "Iveskite pazymius. Tam kad sustabdyti ivedima parasykite 33:\n";
        do {
            inputOrNum = gradeInput();
            if(inputOrNum == 33) break;

            // if(nd_vec.size() == nd_vec.capacity()) nd_vec.reserve(resSpace*2);

            nd_vec.push_back(inputOrNum);

        } while(cin.eofbit);

        // nd_vec.shrink_to_fit();

        cout << "Iveskite egzamino paz.:\n";
        egz = gradeInput();
    }

    else {
        cout << "Iveskite pazymiu skaiciu (egzamino pazymys neieina i nurodyta skaiciu):\n";
        inputOrNum = autoGradeInput();

        int tempNum;
        for(int i=0; i<inputOrNum; i++) {
            tempNum = randomSkaicius();
            nd_vec.push_back(tempNum); 
        }
        egz = randomSkaicius();
    }

    if (nd_vec.size() != 0) {
        temp.galutinisVid = 0.4 * (skaicVid(nd_vec)) + 0.6 * egz;
        temp.galutinisMed = 0.4 * (skaicMed(nd_vec)) + 0.6 * egz;
    }
    else {
        temp.galutinisVid = 0.6 * egz;
        temp.galutinisMed = 0.6 * egz;
    }

    nd_vec.clear();

    cout << "---Duomenys irasyti---\n";
}

void output_template() {
    cout << setw(15) << left << "\nVardas" << setw(20) << left << "Pavarde" <<
    setw(34) << left << "Galutinis(Vid.) / Galutinis (Med.)\n";
    cout << "---------------------------------------------------------------------\n";
}

void spausd(studentas_v &temp, string outputPasirinkimas) {
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

void spausd(studentas_d &temp, string outputPasirinkimas) {
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

void spausd(studentas_l &temp, string outputPasirinkimas) {
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

bool regexPalyginimas(const studentas_v& a, const studentas_v& b) {
    regex vardoStruktura("[^0-9]*([0-9]+)");
    smatch aMatch, bMatch;
    regex_search(a.vardas, aMatch, vardoStruktura);
    regex_search(b.vardas, bMatch, vardoStruktura);
    int aNumber = stoi(aMatch[1].str());
    int bNumber = stoi(bMatch[1].str());
    if (aNumber != bNumber) {
        return aNumber < bNumber;
    } else {
        return a.pavarde < b.pavarde;
    }
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

int threeInput() {
    int input;

    while(true) {
        try {
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Netinkama ivestis.");
            }
            if (input < 1 || input > 3) {
                throw out_of_range("Pasirinkite 1, 2 arba 3 strategija.");
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