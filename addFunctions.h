#pragma once
#include "mylib.h"

int randomSkaicius();
double skaicVid(vector<int> &paz_vec);
double skaicMed(vector<int> &paz_vec);
void naudotojoIvestis(vector<studentas> &grupe);
void pild(studentas &temp);
void output_template();
void spausd(studentas &temp, string outputPasirinkimas);
bool regexPalyginimas(const studentas& a, const studentas& b);
bool getBoolInput();
bool isNumber(const string& str);
string getChoiceInput();
string getStringInput();
int gradeInput();
int autoGradeInput();
int strategyInput();