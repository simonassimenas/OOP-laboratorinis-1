#include "addFunctions.h"


void failoGeneravimas();
void failoSkaitymas(list<studentas> &grupe);
void failoIrasymas(list<studentas> &grupe, int partPoint);
int partitionIrSort(list<studentas> &grupe, bool rusiavimasChoice);
bool regexPalyginimas(const studentas& a, const studentas& b);
bool varduPalyginimas(const studentas &a, const studentas &b);
bool vidPalyginimas(const studentas &a, const studentas &b);
bool medPalyginimas(const studentas &a, const studentas &b);
int randomSkaicius();
double skaicVid(list<int> &paz_vec);
double skaicMed(list<int> &paz_vec);
void naudotojoIvestis(list<studentas> &grupe);
void pild(studentas &temp);


int main() {
    list<studentas> grupe;

    cout << "Skaitysite is failo(1) ar pildysite patys(0)?\n";
    bool skaitymas = getBoolInput();
    
    if (skaitymas) {
        failoGeneravimas();

        cout << "Skirstysime pagal vidurki(1) ar mediana(0)\n";
        bool rusiavimasChoice = getBoolInput();

        try {
            failoSkaitymas(grupe);
        }
        catch (const exception &e) {}

        cout << "Rusiuojama...\n";
        int partPoint = partitionIrSort(grupe, rusiavimasChoice);
        failoIrasymas(grupe, partPoint);
    }
    else {
        naudotojoIvestis(grupe);
    }

    grupe.clear();
}

void failoGeneravimas() {
    bool generuoti;
    cout << "Ar norite generuoti faila? (1 - Taip, 0 - Ne)\n";
    generuoti = getBoolInput();

    while (generuoti) {
        cout << "Kiek studentu irasu turetu buti faile?\n";
        int studSk = autoGradeInput();
        cout << "Kiek namu darbu pazymiu turi kiekvienas studentas?\n";
        int ndSk = autoGradeInput();

        auto pradzia = high_resolution_clock::now();

        string filename = "studentai" + to_string(studSk) + ".txt";


        const int bufDydis = 1024 * 1024 * 100;
        char* buferis = new char[bufDydis];
        ofstream fout;
        fout.rdbuf()->pubsetbuf(buferis, bufDydis);
        fout.open(filename);

        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<int> dis(1, 10);

        try {
        if (!fout.is_open()) {
            throw runtime_error("Nepavyko sukurti failo " + filename + " irasymui.");
        }
        else {
            fout << left << setw(19) << "Vardas" << setw(20) << "Pavarde";
            for (int i = 1; i <= ndSk; i++) {
                fout << setw(10) << "ND" + to_string(i);
            }
            fout << setw(10) << "Egz.";

            stringstream ss;
            #pragma omp parallel for
            for (int i = 1; i <= studSk; i++) {
                ss << left << setw(20) << "\nVardas" + to_string(i)
                << setw(20) << "Pavarde" + to_string(i);

                for (int j = 0; j <= ndSk; j++) {
                    int ndGrade = dis(gen);
                    ss << setw(10) << ndGrade;
                }
            }
            #pragma omp critical
            fout << ss.str();
            
            fout.close();
            delete [] buferis;

            auto pabaiga = high_resolution_clock::now();
            duration<double> diff = pabaiga - pradzia;
            cout << "Failo sukūrimas truko " << diff.count() << " sekundes.\n";

            cout << "Ar norite generuoti dar viena faila? (1 - Taip, 0 - Ne)\n";
            generuoti = getBoolInput();
            } 
        }
        catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
        throw e;
        }
    }
}

void failoSkaitymas(list<studentas> &grupe) {
    system("ls *.txt");
    cout << "Iveskite failo pavadinima(is saraso):\n";
    string filename = getStringInput();

    const int bufDydis = 1024 * 1024 * 100;
    char* buferis = new char[bufDydis];
    ifstream fin;
    fin.rdbuf()->pubsetbuf(buferis, bufDydis);
    fin.open(filename);

    try {
        if (!fin.is_open()) {
            throw runtime_error("Nepavyko atverti failo " + filename + " skaitymui.");
        }
        else {
            auto pradzia = high_resolution_clock::now();
            cout << "\nFailas skaitomas...\n";

            int talpa = 100000;
            // grupe.reserve(talpa);

            fin.readsome(buferis, bufDydis);
            int bytesRead = fin.gcount();

            studentas laikinas;
            int pazymys;
            string line;
            getline(fin, line);

            while(fin.peek() != EOF) {
                // if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*10);

                getline(fin, line);
                stringstream ss(line);
                ss >> laikinas.vardas >> laikinas.pavarde;

                while (ss >> pazymys) {
                    laikinas.paz_vec.push_back(pazymys);
                }

                int egz = laikinas.paz_vec.back();
                laikinas.paz_vec.pop_back();

                laikinas.galutinisVid = 0.4 * skaicVid(laikinas.paz_vec) + 0.6 * egz;
                laikinas.galutinisMed = 0.4 * skaicMed(laikinas.paz_vec) + 0.6 * egz;

                laikinas.paz_vec.clear();

                grupe.push_back(laikinas);
            }
            // grupe.shrink_to_fit();
            fin.close();
            delete [] buferis;
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

void failoIrasymas(list<studentas>& grupe, int partPoint) {
    const string filename_v = "vargsai.txt";
    const string filename_s = "saunuoliai.txt";
    ofstream fout_v(filename_v);
    ofstream fout_s(filename_s);

    try {
        if (!fout_v.is_open()) {
            throw runtime_error("Nepavyko sukurti failo " + filename_v + " irasymui.");
        }
        if (!fout_s.is_open()) {
            throw runtime_error("Nepavyko sukurti failo " + filename_s + " irasymui.");
        }
        else {
            cout << "\nRasoma i failus...\n";
            auto pradzia = high_resolution_clock::now();

            fout_v << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            fout_v << string(70, '-') << "\n";
            fout_s << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            fout_s << string(70, '-') << "\n";
            
            for (auto it = grupe.begin(); it != next(grupe.begin(), partPoint); ++it) {
                const auto& temp = *it;
                fout_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            for (auto it = next(grupe.begin(), partPoint); it != grupe.end(); ++it) {
                const auto& temp = *it;
                fout_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }

            fout_v.close();
            fout_s.close();

            auto pabaiga = high_resolution_clock::now();

            duration<double> diff = pabaiga - pradzia;
            cout << "Rasymas i failus truko " << diff.count() << " sekundes.\n";
        }
    }
    catch (const exception& e) {
        cout << "Klaida: " << e.what() << "\n";
    }
}

int partitionIrSort(list<studentas> &grupe, bool rusiavimasChoice) {
    auto it = grupe.begin();

    auto pradzia_part = high_resolution_clock::now();
    if (rusiavimasChoice) {
        grupe.sort(vidPalyginimas);
        it = find_if(grupe.begin(), grupe.end(), [](const studentas& s) { return s.galutinisVid >= 5; });
    }
    else {
        grupe.sort(medPalyginimas);
        it = find_if(grupe.begin(), grupe.end(), [](const studentas& s) { return s.galutinisMed >= 5; });
    }
    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    list<studentas> vargsai(grupe.begin(), it);
    list<studentas> saunuoliai(it, grupe.end());
    //grupe.clear();
    vargsai.sort(varduPalyginimas);
    saunuoliai.sort(varduPalyginimas);
    grupe.splice(grupe.begin(), vargsai);
    int dist = grupe.size();
    grupe.splice(grupe.end(), saunuoliai);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas truko " << diff_sort.count() << " sekundes.\n";
    
    return dist;
}

bool varduPalyginimas(const studentas &a, const studentas &b) {
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}

bool medPalyginimas(const studentas &a, const studentas &b) {
    return a.galutinisMed < b.galutinisMed;
}

bool vidPalyginimas(const studentas &a, const studentas &b) {
    return a.galutinisVid < b.galutinisVid;
}

int randomSkaicius() {
    random_device rd;
    mt19937_64 mt(static_cast<long unsigned int> (rd()));
    uniform_int_distribution<int> dist(0, 10);

    return int(dist(mt));
}

double skaicVid(list<int> &paz_vec) {
    double sum = accumulate(paz_vec.begin(),paz_vec.end(), 0);
    return double(sum / paz_vec.size());
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

void naudotojoIvestis(list<studentas> &grupe) {
    studentas laikinas;
    
    string outputPasirinkimas;
    bool pildyti;
    int talpa = 16;

    // grupe.reserve(talpa);

    cout << "Skaiciuosime vidurki(v), mediana(m) ar abu(a)?\n";
    outputPasirinkimas = getChoiceInput();

    cout << "Ar norite pildyti irasa? (1 - Taip, 0 - Ne)\n";
    pildyti = getBoolInput();

    while(pildyti) {
        // if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*2);

        pild(laikinas);
        grupe.push_back(laikinas);

        cout << "Ar norite pildyti dar viena irasa? (1 - Taip, 0 - Ne)\n";
        pildyti = getBoolInput();
    }
    // grupe.shrink_to_fit();

    output_template();
    for (auto it = grupe.begin(); it != grupe.end(); ++it) {
    spausd(*it, outputPasirinkimas);
}
}

void pild(studentas &temp) {
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