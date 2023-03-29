#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <regex>
#include <omp.h>
#include <execution>
#include <list>
#include <deque>

using namespace std::chrono;

using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::string;
using std::copy;
using std::isdigit;
using std::min;
using std::numeric_limits;
using std::streamsize;
using std::vector;
using std::size_t;
using std::sort;
using std::accumulate;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::stoi;
using std::getline;
using std::smatch;
using std::regex;
using std::regex_search;
using std::exit;
using std::fixed;
using std::invalid_argument;
using std::out_of_range;
using std::exception;
using std::runtime_error;
using std::to_string;
using std::find_if;
using std::distance;
using std::partition;
using std::sort;
using std::list;
using std::deque;
using std::next;
using std::back_inserter;
using std::move;
using std::merge;
using std::stable_sort;


struct studentas {
    string vardas = "", pavarde = "";
    double galutinisVid = 0, galutinisMed = 0;
    vector<int> paz_vec;
    // list<int> paz_vec;
    // deque<int> paz_vec;
};