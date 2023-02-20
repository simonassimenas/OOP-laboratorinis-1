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

    vector<studentas> grupe;

    int irasai = 0;
    bool vidMed;

    cout << "Iveskite irasu skaiciu:\n";                    //turi but dinaminiskai studentai ir su c masyvu
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

    grupe.resize(irasai);

    for(int i=0; i<irasai; i++) pild(grupe[i]);

    output_template();
    for(int i=0; i<irasai; i++) spausd(grupe[i], vidMed);

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
    cout << "Rankinis pazymiu ivedimas(1) arba atsitiktinis generavimas(0)?\n";
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
        cout << "Iveskite pazymiu skaiciu:\n";
        cin >> inputOrNum;
        int tempNum;

        nd_vec.resize(inputOrNum);

        for(int i=0; i<inputOrNum; i++) {
            tempNum = rand() % 11;
            nd_vec.push_back(tempNum); 
        }
        temp.egz = rand() % 11;
    }

    temp.vid = skaicVid(&nd_vec[0], nd_vec.size());
    temp.med = skaicMed(&nd_vec[0], nd_vec.size());

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

double skaicVid(int *paz_mas, int paz_sk) {     //ar cia turetu buti const vector<int>?
    double result = 0;
    for(int i=0; i<paz_sk; i++) {
        result += paz_mas[i];
    }
    return result/paz_sk;
}

double skaicMed(int *paz_mas, int paz_sk) {      //ar cia turetu buti const vector<int>?
    for(int i=0; i<paz_sk-1; i++) {             //pakeist kad butu naudojamas sort su vektoriumi
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