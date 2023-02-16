#include "mylib.h"

struct studentas {
    string vardas = "", pavarde = "";
    int *paz = nullptr;
    int egz = 0;
};

void pild(studentas &temp, int paz_sk);
void spausd(studentas &temp, int paz_sk, bool vidMed);

int main() {
    int irasai = 0, paz_sk = 0;
    bool vidMed;

    cout << "Iveskite irasu skaiciu:\n";
    cin >> irasai;
    cout << "Iveskite namu darbu skaiciu:\n";
    cin >> paz_sk;
    cout << "Skaiciuosime vidurki(1) ar mediana(0)? Iprastinis pasirinkimas: vidurkis\n";
    cin>>vidMed;

    studentas *grupe;
    grupe = new studentas[irasai];

    for(int i=0; i<irasai; i++) pild(grupe[i], paz_sk);

    for(int i=0; i<irasai; i++) spausd(grupe[i], paz_sk, vidMed);

    delete [] grupe;
}



void pild(studentas &temp, int paz_sk) {
    cout << "Iveskite varda:\n";
    cin >> temp.vardas;

    cout << "Iveskite pavarde:\n";
    cin >> temp.pavarde;

    int mas[paz_sk];
    cout << "Iveskite " << paz_sk << " paz. nuo 0 iki 10:\n";

    for(int i=0; i<paz_sk; i++) {
        cin >> mas[i];

        if(mas[i]<0 || mas[i]>10) {
            cout << "Iveskite skaiciu 10-baleje sistemoje:\n";
            cin >> mas[i];
        }
    }

    temp.paz = new int [paz_sk];

    for(int j=0; j<paz_sk; j++) {
        temp.paz[j] = mas[j];
    }

    cout<<"Iveskite egzamino paz.:\n";
    cin>>temp.egz;

    cout<<"---Duomenys irasyti---\n";
}

void spausd(studentas &temp, int paz_sk, bool vidMed) {
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;

    if(vidMed) {
        int sum = 0;
        for(int i=0; i<paz_sk; i++) {
            sum += *temp.paz;
        }

        cout << setw(3) << setprecision(3) << 0.6*temp.egz + 0.4*sum/paz_sk << endl;;
    }

    else {
        int mas[paz_sk];

        for(int i=0; i<paz_sk; i++) {
            mas[i] = *temp.paz;
        } 

        for(int i=0; i<paz_sk-1; i++) {
            for(int j=0; j<paz_sk-i-1; j++) {
                swap(mas[j], mas[j+1]);
            }
        }


        if(paz_sk%2 == 0) {
            double median = (mas[paz_sk/2]+mas[paz_sk+1])/2;
            cout << setw(3) << setprecision(3) << median;
        }

        else {
            cout << setw(3) << setprecision(3) << mas[int(paz_sk/2+0.5)];
        }
    }
    
    delete [] temp.paz;
}