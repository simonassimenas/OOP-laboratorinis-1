#include "mylib.h"

struct studentas {
    string vardas = "", pavarde = "";
    double vid = 0, med = 0;
    int egz = 0;
};

void pild(studentas &temp);
void spausd(studentas &temp, bool vidMed);
double skaicVid(int *paz_mas, int paz_sk);
double skaicMed(int *paz_mas, int paz_sk);
bool isNumber(const string& str);
void output_template();

int main() {
    srand(time(NULL));

    int irasai = 0;
    bool vidMed;

    cout << "Iveskite irasu skaiciu:\n";
    cin >> irasai;
    while(irasai < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite teigiama skaiciu:\n";
        cin >> irasai;
    }

    cout << "Skaiciuosime vidurki(1) ar mediana(0)?\n";
    cin>>vidMed;
    while(!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
        cin >> vidMed;
    }

    studentas *grupe;
    grupe = new studentas[irasai];

    for(int i=0; i<irasai; i++) pild(grupe[i]);

    output_template();
    for(int i=0; i<irasai; i++) spausd(grupe[i], vidMed);

    delete [] grupe;
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
    cout << "Rankinis pazymiu ivedimas(1) arba atsitiktinis generavimas(0)?\n";
    cin >> rankinis;
    while(!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Iveskite 1 arba 0:\n";
        cin >> rankinis;
    }

    if(rankinis) {

        cout << "Iveskite pazymius. Tam kad sustabdyti ivedima parasykite 33:\n";

        int talpa = 1;
        int* nd_mas = new int [talpa];
        int nd_skaicius = 0;

        do {
            cin >> nd_mas[nd_skaicius];

            if(nd_mas[nd_skaicius] == 33) break;

            while(!cin || nd_mas[nd_skaicius]<0 || nd_mas[nd_skaicius]>10) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Iveskite skaiciu 10-baleje sistemoje:\n";
                cin >> nd_mas[nd_skaicius];
            }
            nd_skaicius++;

            if (nd_skaicius == talpa) {
                talpa *= 2;
                int* naujas_mas = new int[talpa];
                for (int i = 0; i < nd_skaicius; i++) {
                    naujas_mas[i] = nd_mas[i];
                }
                delete[] nd_mas;
                nd_mas = naujas_mas;
            }
        } while(cin.eofbit);

        temp.vid = skaicVid(nd_mas, nd_skaicius);
        temp.med = skaicMed(nd_mas, nd_skaicius);

        cout<<"Iveskite egzamino paz.:\n";
        cin>>temp.egz;
    }

    else {
        int nd_skaicius;

        cout << "Iveskite pazymiu skaiciu:\n";
        cin >> nd_skaicius;

        int nd_mas[nd_skaicius];

        for(int i=0; i<nd_skaicius; i++) {
            nd_mas[i] = rand() % 11;
        }

        temp.vid = skaicVid(nd_mas, nd_skaicius);
        temp.med = skaicMed(nd_mas, nd_skaicius);

        temp.egz = rand() % 11;
    }

    cout<<"---Duomenys irasyti---\n";
}

void spausd(studentas &temp, bool vidMed) {
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;

    if(vidMed)
        cout << setw(3) << setprecision(3) << 0.6*temp.egz + 0.4*temp.vid << endl;
    else
        cout << setw(3) << setprecision(3) << 0.6*temp.egz + 0.4*temp.med << endl;
}

double skaicVid(int *paz_mas, int paz_sk) {
    double result = 0;
    for(int i=0; i<paz_sk; i++) {
        result += paz_mas[i];
    }
    return result/paz_sk;
}

double skaicMed(int *paz_mas, int paz_sk) {
    for(int i=0; i<paz_sk-1; i++) {
        for(int j=0; j<paz_sk-i-1; j++) {
            swap(paz_mas[j], paz_mas[j+1]);
        }
    }

    if(paz_sk%2 == 0)
        return double((paz_mas[paz_sk/2] + paz_mas[paz_sk+1]) / 2);
    else
        return double((paz_mas[paz_sk/2-1] + paz_mas[paz_sk/2]) / 2);
}

bool isNumber(const string& str) {
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

void output_template() {
    cout << setw(15) << left << "\nVardas" << setw(20) << left << "Pavarde" <<
    setw(24) << left << "Galutinis(Vid.) / Galutinis (Med.)\n";
    cout << "--------------------------------------------------------------------\n";
}