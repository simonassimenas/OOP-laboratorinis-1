#include "addFunctions.h"


void failoSkaitymas(vector<studentas> &grupe);
void failoIrasymas(vector<studentas> &grupe);
void pazPalyginimas(vector<studentas> & grupe, bool rusiavimoPas);
bool regexPalyginimas(const studentas& a, const studentas& b);
bool varduPalyginimas(const studentas &a, const studentas &b);
int randomSkaicius();
double skaicVid(vector<int> &paz_vec);
double skaicMed(vector<int> &paz_vec);
void naudotojoIvestis(vector<studentas> &grupe);
void pild(studentas &temp);


int main() {
    vector<studentas> grupe;

    cout << "Skaitysite is failo(1) ar pildysite patys(0)?\n";
    bool skaitymas = getBoolInput();
    
    if (skaitymas) {
        try {
            failoSkaitymas(grupe);
        }
        catch (const exception &e) {}

        cout << "Skirstysime pagal vidurki(1) ar mediana(0)\n";
        bool rusiavimasChoice = getBoolInput();

        //timeint
        pazPalyginimas(grupe, rusiavimasChoice);
        //end timinimo



        failoIrasymas(grupe);
    }
    else {
        naudotojoIvestis(grupe);
    }

    grupe.clear();
}

void failoGeneravimas(int studSk, int ndSk) {
    ofstream fout;
    int studCount = 0;
    int ndCount = 0;
    
    //pradiniu 2 eiluciu ir visur sudet kiek space reserved

    while (studCount > studSk) {
        fout << "Vardas" + to_string(studCount);
        fout << "Pavarde" + to_string(studCount);

        while (ndCount > (ndSk + 1)) {
            fout << randomSkaicius();
        }
    }
}



void failoSkaitymas(vector<studentas> &grupe) {
    system("ls *.txt");
    cout << "Iveskite failo pavadinima(is saraso):\n";
    string filename = getStringInput();

    int bufDydis = 1024;
    vector<char> buferis;
    buferis.resize(bufDydis);
    ifstream fin;
    fin.rdbuf()->pubsetbuf(&buferis[0], bufDydis);
    fin.open(filename);

    try {
        if (!fin.is_open()) {
            throw runtime_error("Nepavyko atverti failo " + filename + " skaitymui.");
        }
        else {
            auto pradzia = high_resolution_clock::now();
            cout << "Failas skaitomas...\n";

            int talpa = 10000;
            grupe.reserve(talpa);

            studentas laikinas;
            int pazymys;
            string line;
            getline(fin, line);

            while(fin.peek() != EOF) {
                if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*2);

                getline(fin, line);
                stringstream ss(line);
                ss >> laikinas.vardas >> laikinas.pavarde;

                vector<int> paz_vec;
                while (ss >> pazymys) {
                    paz_vec.push_back(pazymys);
                }

                int egz = paz_vec.back();
                paz_vec.pop_back();

                laikinas.galutinisVid = 0.4 * skaicVid(paz_vec) + 0.6 * egz;
                laikinas.galutinisMed = 0.4 * skaicMed(paz_vec) + 0.6 * egz;

                paz_vec.clear();

                grupe.push_back(laikinas);
            }
            grupe.shrink_to_fit();
            fin.close();
            buferis.clear();
            auto pabaigaSkait = high_resolution_clock::now();

            cout << "Duomenys nuskaityti\n";

            std::chrono::duration<double> diffSkait = pabaigaSkait - pradzia;
            cout << "\nSkaitymas truko " << diffSkait.count() << " sekundes.\n\n";
        }
    }
    catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
        throw e;
    }
}

void failoIrasymas(vector<studentas> &grupe) {
    const string filename = "kursiokai.txt";
    ofstream fout(filename);

    try {
        if (!fout.is_open()) {
            throw runtime_error("Nepavyko sukurti failo " + filename + " irasymui.");
        }
        else {
            auto pradzia = high_resolution_clock::now();
            cout << "Rasoma i faila...\n";

            fout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            fout << string(70, '-') << "\n";

            for (const auto &temp : grupe) {
                fout << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout.close();
            auto pabaiga = high_resolution_clock::now();

            cout << "Duomenys irasyti\n";

            duration<double> diff = pabaiga - pradzia;
            cout << "\nRasymas truko " << diff.count() << " sekundes.\n";
        }
    }
    catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
    }
}

// gal geriau rusiavimui ir atskyrimui naudot partition?
int atskyrimas(vector<studentas>& grupe, bool rusiavimasChoice) {
    auto it = grupe.end();

    if (rusiavimasChoice) {
        it = find_if(grupe.begin(), grupe.end(), [](const studentas& s) { return s.galutinisVid >= 5; });
    }
    else {
        it = find_if(grupe.begin(), grupe.end(), [](const studentas& s) { return s.galutinisMed >= 5; });
    }

    return int(distance(grupe.begin(), it));
}

void pazPalyginimas(vector<studentas> &grupe, bool rusiavimoPas) {
    if (rusiavimoPas) {
        auto pradzia = high_resolution_clock::now();
        sort(grupe.begin(), grupe.end(), vidPalyginimas); 
        auto pabaiga = high_resolution_clock::now();
        duration<double> diffSort = pabaiga - pradzia;
        cout << "Rusiavimas pagal vidurki truko " << diffSort.count() << " sekundes.\n\n";
    }
    else {
        auto pradzia = high_resolution_clock::now();
        sort(grupe.begin(), grupe.end(), medPalyginimas); 
        auto pabaiga = high_resolution_clock::now();
        duration<double> diffSort = pabaiga - pradzia;
        cout << "Rusiavimas pagal mediana truko " << diffSort.count() << " sekundes.\n\n";
    }
}

// Grazus bet letas
bool regexPalyginimas(const studentas& a, const studentas& b) {
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

// Greitas bet negrazus
bool varduPalyginimas(const studentas &a, const studentas &b) {
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}

bool medPalyginimas(const studentas &a, const studentas &b) {
    return a.galutinisMed > b.galutinisMed;
}

bool vidPalyginimas(const studentas &a, const studentas &b) {
    return a.galutinisVid > b.galutinisVid;
}

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

void naudotojoIvestis(vector<studentas> &grupe) {
    studentas laikinas;
    
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

void pild(studentas &temp) {
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