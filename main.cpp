#include "mylib.h"

struct studentas {
    string vardas = "", pavarde = "";
    double vid = 0, med = 0;
    int egz = 0;
};

void pild(studentas &temp);
void spausd(studentas &temp, bool vidMed);
double skaicVid(vector<int> &paz_vec);
double skaicMed(vector<int> &paz_vec);
bool isNumber(const string& str);
int randomSkaicius();
void output_template();

int main() {
    vector<studentas> grupe;
    studentas laikinas;

    bool vidMed, pildyti;
    int talpa = 16;

    grupe.reserve(talpa);

    cout << "Skaiciuosime vidurki(1) ar mediana(0)?\n";
    cin>>vidMed;
    while(!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
        cin >> vidMed;
    }

    cout << "Ar norite pildyti irasa? (1 - Taip, 0 - Ne)\n";
    cin >> pildyti;
    while(!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
        cin >> pildyti;
    }

    while(pildyti) {
        while(!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Iveskite 1 arba 0:\n";
            cin >> pildyti;
        }

        if(grupe.size() == grupe.capacity()) grupe.reserve(talpa*2);

        pild(laikinas);
        grupe.push_back(laikinas);

        cout << "Ar norite pildyti dar viena irasa? (1 - Taip, 0 - Ne)\n";
        cin >> pildyti;
        while(!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Iveskite 1 arba 0:\n";
            cin >> pildyti;
        }
    }
    grupe.shrink_to_fit();

    output_template();
    for(int i=0; i<grupe.size(); i++) spausd(grupe[i], vidMed);

    grupe.clear();
}



void pild(studentas &temp) {
    cout << "Iveskite varda:\n";
    cin >> temp.vardas;
    if(isNumber(temp.vardas)) {
        cout << "Netinkama ivestis. Iveskite varda dar karta:\n";
        cin >> temp.vardas;
    }

    cout << "Iveskite pavarde:\n";
    cin >> temp.pavarde;
    if(isNumber(temp.pavarde)) {
        cout << "Netinkama ivestis. Iveskite pavarde dar karta:\n";
        cin >> temp.pavarde;
    }

    bool rankinis;
    cout << "Rankinis pazymiu ivedimas(1) arba automatinis generavimas(0)?\n";
    cin >> rankinis;
    while(!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
        cin >> rankinis;
    }

    vector<int> nd_vec;
    int resSpace = 16;
    nd_vec.reserve(resSpace);
    int inputOrNum;

    if(rankinis) {
        cout << "Iveskite pazymius. Tam kad sustabdyti ivedima parasykite 33:\n";

        do {
            cin >> inputOrNum;
            if(inputOrNum == 33) break;
            
            while(!cin || inputOrNum<0 || inputOrNum>10) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Iveskite skaiciu 10-baleje sistemoje:\n";
                cin >> inputOrNum;
            }

            if(nd_vec.size() == nd_vec.capacity()) nd_vec.reserve(resSpace*2);

            nd_vec.push_back(inputOrNum);

        } while(cin.eofbit);

        nd_vec.shrink_to_fit();

        cout<<"Iveskite egzamino paz.:\n";
        cin>>temp.egz;
    }

    else {
        cout << "Iveskite pazymiu skaiciu (egzamino pazymys neieina i nurodyta skaiciu):\n";
        cin >> inputOrNum;
        while(!cin || inputOrNum<1) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Iveskite skaiciu 10-baleje sistemoje:\n";
            cin >> inputOrNum;
        }
        int tempNum;

        for(int i=0; i<inputOrNum; i++) {
            tempNum = randomSkaicius();
            nd_vec.push_back(tempNum); 
        }
        temp.egz = rand() % 11;
    }

    temp.vid = skaicVid(nd_vec);
    temp.med = skaicMed(nd_vec);

    nd_vec.clear();

    cout<<"---Duomenys irasyti---\n";
}

void spausd(studentas &temp, bool vidMed) {
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;

    if(vidMed)
        cout << setw(4) << setprecision(3) << 0.6*temp.egz + 0.4*temp.vid << "\n";
    else
        cout << "                   " << setw(4) << setprecision(3) << 0.6*temp.egz + 0.4*temp.med << "\n";
}

double skaicVid(vector<int> &paz_vec) {
    double sum = 0;
    for(auto& i : paz_vec) sum += i;

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

bool isNumber(const string& str) {
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

int randomSkaicius() {
    random_device rd;
    mt19937_64 mt(static_cast<long unsigned int> (rd()));
    uniform_int_distribution<int> dist(0, 10);

    return int(dist(mt));
}

void output_template() {
    cout << setw(15) << left << "\nVardas" << setw(20) << left << "Pavarde" <<
    setw(24) << left << "Galutinis(Vid.) / Galutinis (Med.)\n";
    cout << "--------------------------------------------------------------------\n";
}