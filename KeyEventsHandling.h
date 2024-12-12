//
// Created by alexisd on 11/12/24.
//

#ifndef KEYEVENTSHANDLING_H
#define KEYEVENTSHANDLING_H

// ----- Includes -----
#include <iostream>
#include <ostream>
#include <string>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <fcntl.h>
#include <chrono>
#include <vector>

using namespace std;

// ----- Constants/Global variables -----
constexpr int nb_features = 4;

// ----- Functions declaration -----
string getKeyboardPath();
libevdev* initDevice(const string& devicePath);
chrono::time_point<chrono::steady_clock>getCurrentTime();
double computeDuration(const chrono::time_point<chrono::steady_clock>& start,const chrono::time_point<chrono::steady_clock>& end);
vector<vector<double>> captureKeyboardEvents(libevdev* dev);
vector<vector<int>> timeToInt(vector<vector<double>> timeMeasure);

#endif //KEYEVENTSHANDLING_H
