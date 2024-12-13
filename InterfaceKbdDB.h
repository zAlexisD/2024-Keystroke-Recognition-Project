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

using namespace std;

// ----- Constants/Global variables -----
const vector<const string> passphraseChoice = {"short","s","medium","m","long","l"};
const vector<const string> passphraseList = {"pouet pouet","we want a long passphrase","rts stands for network telecommunications and security"};
const vector<const string> genderList = {"m","f","male","female","o","other"};
const vector<const string> handednessList = {"r","l","right","left","b","both"};

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
    void setParameter(T UserID::*attribute,const T& paramInterface,const vector<const string>& T& paramList);
    // Setters to make user assign the information
    // Note : ask user as input stream, it is why there is no input in the setters
    void setUsername();
    void setGender();
    void setDominantHand();
    void setPassphrase();
    // Display information method
    void displayUserID();
};

#endif //INTERFACEKBDDB_H
