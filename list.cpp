#include "addFunctions.h"

void failoGeneravimas();
void failoSkaitymas(list<studentas_l> &grupe);
void failoIrasymas_1(list<studentas_l> &saunuoliai, list<studentas_l> &vargsai);
void failoIrasymas_2(list<studentas_l> &grupe, list<studentas_l> &vargsai);
void failoIrasymas_3(list<studentas_l> &grupe, int partPoint);
void splitIrSort(list<studentas_l> &grupe, list<studentas_l> &saunuoliai, 
list<studentas_l> &vargsai, bool rusiavimasChoice);
void singleIrSort(list<studentas_l> &grupe, list<studentas_l> &vargsai, bool rusiavimasChoice);
int findifIrSort(list<studentas_l> &grupe, bool rusiavimasChoice);
bool varduPalyginimas(const studentas_l &a, const studentas_l &b);
bool vidPalyginimas(const studentas_l &a, const studentas_l &b);
bool medPalyginimas(const studentas_l &a, const studentas_l &b);


int main() {
    list<studentas_l> grupe;
    list<studentas_l> saunuoliai;
    list<studentas_l> vargsai;

    int strategy;
    bool choice = true;

    cout << "Skaitysite is failo(1) ar pildysite patys(0)?\n";
    bool skaitymas = getBoolInput();
    
    if (skaitymas) {
        failoGeneravimas();

        while (choice) {
            cout << "Pasirinkite strategija:\n" <<
            "   1 - Du nauji konteineraiai\n" <<
            "   2 - Originalus ir naujas konteineris\n" <<
            "   3 - Find if metodas\n";
            strategy = threeInput();

            cout << "Skirstysime pagal vidurki(1) ar mediana(0)\n";
            bool rusiavimasChoice = getBoolInput();

            try {
                failoSkaitymas(grupe);
            }
            catch (const exception &e) { break; }

            if (strategy == 1) {
                cout << "Rusiuojama...\n";
                splitIrSort(grupe, saunuoliai, vargsai, rusiavimasChoice);
                failoIrasymas_1(saunuoliai, vargsai);
            }
            else if (strategy == 2) {
                cout << "Rusiuojama...\n";
                singleIrSort(grupe, vargsai, rusiavimasChoice);
                failoIrasymas_2(grupe, vargsai);
            }
            else {
                cout << "Rusiuojama...\n";
                int partPoint = findifIrSort(grupe, rusiavimasChoice);
                failoIrasymas_3(grupe, partPoint);
            }
            cout << "\nAr norite isbandyti dar viena strategija? (1 - Taip, 0 - Ne)\n";
            choice = getBoolInput();
            if (choice) {
                system("make cleanres");
            }
        }
    }
    else {
        naudotojoIvestis(grupe);
        grupe.clear();
    }
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

void failoSkaitymas(list<studentas_l> &grupe) {
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

            fin.readsome(buferis, bufDydis);
            int bytesRead = fin.gcount();

            studentas_l laikinas;
            int pazymys;
            string line;
            getline(fin, line);

            while(fin.peek() != EOF) {
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

void failoIrasymas_1(list<studentas_l> &saunuoliai, list<studentas_l> &vargsai) {
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

            stringstream oss_v;
            stringstream oss_s;

            oss_v << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";
            oss_v << string(70, '-') << "\n";

            oss_s << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            oss_s << string(70, '-') << "\n";

            for (auto &temp: vargsai) {
                fout_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (auto &temp: saunuoliai) {
                fout_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_s << oss_s.str();

            fout_v.close();
            fout_s.close();

            auto pabaiga = high_resolution_clock::now();

            duration<double> diff = pabaiga - pradzia;
            cout << "Rasymas i failus truko " << diff.count() << " sekundes.\n";

            saunuoliai.clear();
            vargsai.clear();
        }
    }
    catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
    }
}

void failoIrasymas_2(list<studentas_l> &grupe, list<studentas_l> &vargsai) {
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

            stringstream oss_v;
            stringstream oss_s;

            oss_v << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";
            oss_v << string(70, '-') << "\n";

            oss_s << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            oss_s << string(70, '-') << "\n";

            for (auto &temp: vargsai) {
                fout_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (auto &temp: grupe) {
                fout_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_s << oss_s.str();

            fout_v.close();
            fout_s.close();

            auto pabaiga = high_resolution_clock::now();

            duration<double> diff = pabaiga - pradzia;
            cout << "Rasymas i failus truko " << diff.count() << " sekundes.\n";

            grupe.clear();
            vargsai.clear();
        }
    }
    catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
    }
}

void failoIrasymas_3(list<studentas_l>& grupe, int partPoint) {
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

            stringstream oss_v;
            stringstream oss_s;

            oss_v << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";
            oss_v << string(70, '-') << "\n";

            oss_s << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
                << setw(18) << "Galutinis (Vid.) / " << setw(16) << "Galutinis (Med.)\n";

            oss_s << string(70, '-') << "\n";
            
            for (auto it = grupe.begin(); it != next(grupe.begin(), partPoint); ++it) {
                const auto& temp = *it;
                oss_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (auto it = next(grupe.begin(), partPoint); it != grupe.end(); ++it) {
                const auto& temp = *it;
                oss_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_s << oss_v.str();

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

void splitIrSort(list<studentas_l> &grupe, list<studentas_l> &saunuoliai, 
list<studentas_l> &vargsai, bool rusiavimasChoice) {
    auto pradzia_part = high_resolution_clock::now();

    if (rusiavimasChoice) {
        for(auto &i: grupe) {
            if (i.galutinisVid < 5)
                vargsai.push_back(i);
            else
                saunuoliai.push_back(i);
        }
    }
    else {
        for(auto &i: grupe) {
            if (i.galutinisMed < 5)
                vargsai.push_back(i);
            else
                saunuoliai.push_back(i);
        }
    }

    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    saunuoliai.sort(varduPalyginimas);
    vargsai.sort(varduPalyginimas);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";

    grupe.clear();
}

void singleIrSort(list<studentas_l> &grupe, list<studentas_l> &vargsai, bool rusiavimasChoice) {
    auto pradzia_part = high_resolution_clock::now();

    if (rusiavimasChoice) {
    copy_if(grupe.begin(), grupe.end(), back_inserter(vargsai), [](const studentas_l& a) { return a.galutinisVid < 5; });
    grupe.remove_if([](const studentas_l& a) { return a.galutinisVid < 5; });
    }
    else {
        copy_if(grupe.begin(), grupe.end(), back_inserter(vargsai), [](const studentas_l& a) { return a.galutinisVid < 5; });
        grupe.remove_if([](const studentas_l& a) { return a.galutinisVid < 5; });
    }

    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    grupe.sort(varduPalyginimas);
    vargsai.sort(varduPalyginimas);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";
}

int findifIrSort(list<studentas_l> &grupe, bool rusiavimasChoice) {
    auto it = grupe.begin();

    auto pradzia_part = high_resolution_clock::now();
    if (rusiavimasChoice) {
        grupe.sort(vidPalyginimas);
    }
    else {
        grupe.sort(medPalyginimas);
    }

    if (rusiavimasChoice) {
        it = find_if(grupe.begin(), grupe.end(), [](const studentas_l& s) { return s.galutinisVid >= 5; });
    }
    else {
        it = find_if(grupe.begin(), grupe.end(), [](const studentas_l& s) { return s.galutinisMed >= 5; });
    }
    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    list<studentas_l> vargsai(grupe.begin(), it);
    list<studentas_l> saunuoliai(it, grupe.end());

    vargsai.sort(varduPalyginimas);
    saunuoliai.sort(varduPalyginimas);
    grupe.splice(grupe.begin(), vargsai);
    int dist = grupe.size();
    grupe.splice(grupe.end(), saunuoliai);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;

    cout << "Atskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";
    
    return dist;
}

bool varduPalyginimas(const studentas_l &a, const studentas_l &b) {
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}

bool vidPalyginimas(const studentas_l &a, const studentas_l &b) {
    return a.galutinisVid < b.galutinisVid;
}

bool medPalyginimas(const studentas_l &a, const studentas_l &b) {
    return a.galutinisMed < b.galutinisMed;
}