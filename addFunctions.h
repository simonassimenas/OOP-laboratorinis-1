#pragma once
#include "mylib.h"

int randomSkaicius();
double skaicVid(vector<int> &paz_vec);
double skaicVid(deque<int> &paz_vec);
double skaicVid(list<int> &paz_vec);
double skaicMed(vector<int> &paz_vec);
double skaicMed(deque<int> &paz_vec);
double skaicMed(list<int> &paz_vec);
void naudotojoIvestis(vector<studentas_v> &grupe);
void naudotojoIvestis(deque<studentas_d> &grupe);
void naudotojoIvestis(list<studentas_l> &grupe);
void pild(studentas_v &temp);
void pild(studentas_d &temp);
void pild(studentas_l &temp);
void output_template();
void spausd(studentas_v &temp, string outputPasirinkimas);
void spausd(studentas_d &temp, string outputPasirinkimas);
void spausd(studentas_l &temp, string outputPasirinkimas);
bool regexPalyginimas(const studentas_v& a, const studentas_v& b);
bool getBoolInput();
bool isNumber(const string& str);
string getChoiceInput();
string getStringInput();
int gradeInput();
int autoGradeInput();
int threeInput();