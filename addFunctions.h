#pragma once
#include "mylib.h"

void output_template();
void spausd(studentas &temp, string outputPasirinkimas);

bool regexPalyginimas(const studentas& a, const studentas& b);

bool getBoolInput();
bool isNumber(const string& str);
string getChoiceInput();
string getStringInput();
int gradeInput();
int autoGradeInput();