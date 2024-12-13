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
#include <map>

using namespace std;

// ----- Constants/Global variables -----
constexpr int nb_features = 4;
constexpr double multiplier = 1e8;
// Map keycodes to characters
const map<int,char> key_mapping_QWERTY = {
    {KEY_A, 'a'}, {KEY_B, 'b'}, {KEY_C, 'c'}, {KEY_D, 'd'}, {KEY_E, 'e'},
    {KEY_F, 'f'}, {KEY_G, 'g'}, {KEY_H, 'h'}, {KEY_I, 'i'}, {KEY_J, 'j'},
    {KEY_K, 'k'}, {KEY_L, 'l'}, {KEY_M, 'm'}, {KEY_N, 'n'}, {KEY_O, 'o'},
    {KEY_P, 'p'}, {KEY_Q, 'q'}, {KEY_R, 'r'}, {KEY_S, 's'}, {KEY_T, 't'},
    {KEY_U, 'u'}, {KEY_V, 'v'}, {KEY_W, 'w'}, {KEY_X, 'x'}, {KEY_Y, 'y'},
    {KEY_Z, 'z'}, {KEY_SPACE, ' '}
    };
// Issue : my key events handling is in QWERTY, but I have an AZERTY keyboard
const map<int, char> key_mapping_AZERTY = {
    {KEY_Q, 'a'}, {KEY_W, 'z'}, {KEY_E, 'e'}, {KEY_R, 'r'}, {KEY_T, 't'},
        {KEY_Y, 'y'}, {KEY_U, 'u'}, {KEY_I, 'i'}, {KEY_O, 'o'}, {KEY_P, 'p'},
        {KEY_A, 'q'}, {KEY_S, 's'}, {KEY_D, 'd'}, {KEY_F, 'f'}, {KEY_G, 'g'},
        {KEY_H, 'h'}, {KEY_J, 'j'}, {KEY_K, 'k'}, {KEY_L, 'l'}, {KEY_SEMICOLON, 'm'},
        {KEY_Z, 'w'}, {KEY_X, 'x'}, {KEY_C, 'c'}, {KEY_V, 'v'}, {KEY_B, 'b'},
        {KEY_N, 'n'}, {KEY_M, 'm'}, {KEY_SPACE, ' '},
};

// ----- Class declaration -----
class KeyCapture {
private :
    // Attributes
    vector<vector<double>> timeMeasure;
    string userInput;
public:
    // Default constructor
    KeyCapture();
    // Getters
    vector<vector<double>> getTimeMeasure();
    string getUserInput();
    // Methods
    void addTimeMeasure(int row_index,double duration);
    void addCharacter(int key_code);
    void resetCapture();
};

// ----- Functions declaration -----
string getKeyboardPath();
libevdev* initDevice(const string& devicePath);
chrono::time_point<chrono::steady_clock>getCurrentTime();
double computeDuration(const chrono::time_point<chrono::steady_clock>& start,const chrono::time_point<chrono::steady_clock>& end);
KeyCapture captureKeyboardEvents(libevdev* dev);
vector<int> timeToData(const vector<vector<double>>& timeMeasure);

#endif //KEYEVENTSHANDLING_H
