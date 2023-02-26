#include "mylib.h"
#include "addFunctions.h"


void failoSkaitymas(vector<studentas> &grupe);
void failoIrasymas(vector<studentas> &grupe);
void naudotojoIvestis(vector<studentas> &grupe);
void pild(studentas &temp);
bool palyginimas(const studentas& a, const studentas& b);


int main() {
    vector<studentas> grupe;

    cout << "Skaitysite is failo(1) ar pildysite patys(0)?\n";
    bool skaitymas = getBoolInput();

    if(skaitymas) {
        failoSkaitymas(grupe);

        failoIrasymas(grupe);
    }
    else {
        naudotojoIvestis(grupe);
    }

    grupe.clear();
}

void failoSkaitymas(vector<studentas> &grupe) {
    // system("dir");
    // system("pause");
    const string filename = "studentai1000000.txt";

    // cout << "Iveskite failo pavadinima:\n";
    // filename = getStringInput();

    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Nepavyko atverti failo skaitymui.\n";
    }
    else {
        auto pradzia = std::chrono::high_resolution_clock::now();
        cout << "Failas skaitomas...\n";

        int talpa = 1000000;
        grupe.reserve(talpa);

        studentas laikinas;
        int pazymys;
        string line;
        getline(fin, line);

        while (getline(fin, line)) {
            if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*2);

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
        auto pabaigaSkait = std::chrono::high_resolution_clock::now();

        cout << "Duomenys nuskaityti\n";

        std::chrono::duration<double> diffSkait = pabaigaSkait - pradzia;
        cout << "\nSkaitymas truko " << diffSkait.count() << " sekundes.\n\n";
    }
}

void failoIrasymas(vector<studentas> &grupe) {
    const string filename = "kursiokai.txt";
    ofstream fout(filename);

    if (!fout.is_open()) {
        cout << "Nepavyko sukurti failo" << filename << "irasymui.\n";
    }
    else {
        auto pradzia = std::chrono::high_resolution_clock::now();
        cout << "Rasoma i faila...\n";

        //sort(grupe.begin(), grupe.end(), palyginimas);            //sutvarkyt sortinima

        fout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" 
            << setw(18) << "Galutinis (Vid.) / " << setw(20) << "Galutinis (Med.)\n";

        fout << string(70, '-') << "\n";                            //kodel padeda taba pradzioj

        for (const auto &temp : grupe) {
            fout << left << setw(15) << temp.vardas << setw(21) << temp.pavarde 
                << setw(19) << setprecision(3) << temp.galutinisVid 
                << setw(20) << setprecision(3) << temp.galutinisMed << "\n";
        }
        fout.close();
        auto pabaiga = std::chrono::high_resolution_clock::now();

        cout << "Duomenys irasyti\n";

        std::chrono::duration<double> diff = pabaiga - pradzia;
        cout << "\nRasymas truko " << diff.count() << " sekundes.\n";
    }
}

// bool palyginimas(const studentas& a, const studentas& b) {      //labai leta
//     regex vardoStruktura("[^0-9]*([0-9]+)");
//     smatch aMatch, bMatch;
//     regex_search(a.vardas, aMatch, vardoStruktura);
//     regex_search(b.vardas, bMatch, vardoStruktura);
//     int aNumber = stoi(aMatch[1].str());
//     int bNumber = stoi(bMatch[1].str());
//     if (aNumber != bNumber) {
//         return aNumber < bNumber;
//     } else {
//         return a.pavarde < b.pavarde;
//     }
// }

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
        cin >> egz;
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

