#include "addFunctions.h"

void failoGeneravimas();
void failoSkaitymas(deque<studentas_d> &grupe);
void failoIrasymas_1(deque<studentas_d> &saunuoliai, deque<studentas_d> &vargsai);
void failoIrasymas_2(deque<studentas_d> &grupe, deque<studentas_d> &vargsai);
void failoIrasymas_3(deque<studentas_d> &grupe, int partPoint);
void splitIrSort(deque<studentas_d> &grupe, deque<studentas_d> &saunuoliai, 
deque<studentas_d> &vargsai, bool rusiavimasChoice);
void singleIrSort(deque<studentas_d> &grupe, deque<studentas_d> &vargsai, bool rusiavimasChoice);
int partitionIrSort(deque<studentas_d> &grupe, bool rusiavimasChoice);
bool varduPalyginimas(const studentas_d &a, const studentas_d &b);


int main() {
    deque<studentas_d> grupe;
    deque<studentas_d> saunuoliai;
    deque<studentas_d> vargsai;

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
            "   3 - Partition metodas\n";
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
                int partPoint = partitionIrSort(grupe, rusiavimasChoice);
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

void failoSkaitymas(deque<studentas_d> &grupe) {
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

            studentas_d laikinas;
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
            grupe.shrink_to_fit();
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

void failoIrasymas_1(deque<studentas_d> &saunuoliai, deque<studentas_d> &vargsai) {
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
                oss_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (auto &temp: saunuoliai) {
                oss_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
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

void failoIrasymas_2(deque<studentas_d> &grupe, deque<studentas_d> &vargsai) {
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
                oss_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (auto &temp: grupe) {
                oss_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
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

void failoIrasymas_3(deque<studentas_d> &grupe, int partPoint) {
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

            for (int i = 0; i < partPoint; i++) {
                const auto& temp = grupe[i];
                oss_v << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                    << setw(19) << fixed << setprecision(2) << temp.galutinisVid 
                    << setw(20) << fixed << setprecision(2) << temp.galutinisMed << "\n";
            }
            fout_v << oss_v.str();

            for (int i = partPoint; i < grupe.size(); i++) {
                const auto& temp = grupe[i];
                oss_s << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
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
        }
    }
    catch (const exception &e) {
        cout << "Klaida: " << e.what() << "\n";
    }
}

void splitIrSort(deque<studentas_d> &grupe, deque<studentas_d> &saunuoliai, 
deque<studentas_d> &vargsai, bool rusiavimasChoice) {
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
    vargsai.shrink_to_fit();
    saunuoliai.shrink_to_fit();

    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    sort(saunuoliai.begin(), saunuoliai.end(), varduPalyginimas);
    sort(vargsai.begin(), vargsai.end(), varduPalyginimas);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";

    grupe.clear();
}

void singleIrSort(deque<studentas_d> &grupe, deque<studentas_d> &vargsai, bool rusiavimasChoice) {
    auto pradzia_part = high_resolution_clock::now();

    if (rusiavimasChoice) {
        auto vargsai_it = remove_if(grupe.begin(), grupe.end(), [](const studentas_d& a) { return a.galutinisVid < 5; });
        copy(grupe.begin(), vargsai_it, back_inserter(vargsai));
        grupe.erase(grupe.begin(), vargsai_it);
    }
    else {
        auto vargsai_it = remove_if(grupe.begin(), grupe.end(), [](const studentas_d& a) { return a.galutinisVid < 5; });
        copy(grupe.begin(), vargsai_it, back_inserter(vargsai));
        grupe.erase(grupe.begin(), vargsai_it);
    }
    vargsai.shrink_to_fit();

    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    sort(grupe.begin(), grupe.end(), varduPalyginimas);
    sort(vargsai.begin(), vargsai.end(), varduPalyginimas);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";
}

int partitionIrSort(deque<studentas_d> &grupe, bool rusiavimasChoice) {
    auto it = grupe.begin();

    auto pradzia_part = high_resolution_clock::now();
    if (rusiavimasChoice) {
        it = partition(grupe.begin(), grupe.end(), [](const studentas_d& s) { return s.galutinisVid < 5; });
    }
    else {
        it = partition(grupe.begin(), grupe.end(), [](const studentas_d& s) { return s.galutinisMed < 5; });
    }
    auto pabaiga_part = high_resolution_clock::now();

    auto pradzia_sort = high_resolution_clock::now();
    sort(grupe.begin(), it, varduPalyginimas);
    sort(it, grupe.end(), varduPalyginimas);
    auto pabaiga_sort = high_resolution_clock::now();

    duration<double> diff_part = pabaiga_part - pradzia_part;
    duration<double> diff_sort = pabaiga_sort - pradzia_sort;
    
    cout << "\nAtskyrimas truko " << diff_part.count() << " sekundes.\n";
    cout << "Rusiavimas pagal vardus truko " << diff_sort.count() << " sekundes.\n";

    return static_cast<int>(it - grupe.begin());
}

bool varduPalyginimas(const studentas_d &a, const studentas_d &b) {
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}