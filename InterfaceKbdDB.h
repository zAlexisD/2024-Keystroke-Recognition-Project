//
// Created by alexisd on 12/12/24.
//

#ifndef INTERFACEKBDDB_H
#define INTERFACEKBDDB_H

// ----- Includes -----
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <fstream>

using namespace std;

// ----- Constants/Global variables -----
const vector<string> passphraseChoice = {"short","s","medium","m","long","l"};
const vector<string> passphraseList = {"donut sucre","we want a mid passphrase","rts stands for network telecommunications and security"};
const vector<string> genderList = {"m","f","male","female","o","other"};
const vector<string> handednessList = {"r","l","right","left","b","both"};
constexpr int maxPassphraseAttempt = 10;

// ----- Class declaration -----
// Define a userID class and get from user their username, gender and dominant hand
class UserID {
private:
    // Attributes
    string username;
    string gender;
    string dominantHand;
    string passphrase;
public:
    // Default constructor
    UserID();
    // Getters to get information from the user
    string getUsername();
    string getGender();
    string getDominantHand();
    string getPassphrase();
    // Setters have almost all the same structure so let's define a template method using pointer
    template <typename T>
    void setParameter(T UserID::*attribute,const T& paramInterface,const vector<string>& paramList);
    // Setters to make user assign the information
    // Note : ask user as input stream, it is why there is no input in the setters
    void setUsername();
    void setGender();
    void setDominantHand();
    void setPassphrase();
    // Display information method
    void displayUserID() const;
    // Gather the information we need
    void gatherInformation();
};

// ----- Function declaration -----
vector<vector<int>> getUserData(UserID userSettings,libevdev* dev);
vector<string> genCsvHeader(UserID userID);
void saveCsvData(UserID userSettings,vector<vector<int>> userData);

#endif //INTERFACEKBDDB_H
