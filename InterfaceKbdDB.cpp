//
// Created by alexisd on 12/12/24.
//

#include "InterfaceKbdDB.h"

// UserID Default constructor
UserID::UserID() {
    username = "",gender = "",dominantHand = "";
}

// UserID class getters
string UserID::getUsername() {
    return username;
}
string UserID::getGender() {
    return gender;
}
string UserID::getDominantHand() {
    return dominantHand;
}

// UserID class setters
void UserID::setUsername() {
    // Init
    string usernameInput;
    // User prompt input
    cout << "Hello ! What is your name?"<< endl;
    cin >> usernameInput;
    // Handle non-valid username case = empty entry
    // Note : empty() returns true if the vector or string is empty
    if (usernameInput.empty()){
        while(usernameInput.empty()) {
            cout << "You require a username to continue. Please type a username"<< endl;
            cin >> usernameInput;
        }
    }
    // Assign the user input to the corresponding attribute
    this->username = usernameInput;
}
void UserID::setGender() {
    // Init
    string genderInput;
    // User prompt input
    cout << "What is your gender?(male/female)"<< endl;
    cin >> genderInput;
    // Handle empty entry
    if (genderInput.empty()) {
        while(genderInput.empty()){
            cout << "Please type a gender between 'male' or 'female'"<< endl;
            cin >> genderInput;
        }
    }
    // Handle invalid input (not in the predefined list)
    // Note : find() returns an iterator to the found element in the range of a vector
    // it returns an iterator to vector.end() if the element is not found
    while (ranges::find(genderList.begin(), genderList.end(), genderInput) == genderList.end()) {
        cout << "Please type a gender between 'male' or 'female'"<< endl;
        cin >> genderInput;
    }
    // Assign the user input to the corresponding attribute
    this->gender = genderInput;
}
void UserID::setDominantHand() {
    // Init
    string dominantHandInput;
    // User prompt input
    cout << "What is your strong hand (right/left/both)?"<< endl;
    cin >> dominantHandInput;
    // Handle empty input
    if (dominantHandInput.empty()){
        while(dominantHandInput.empty()) {
            cout << "Please type your handedness (right/left/both)"<< endl;
            cin >> dominantHandInput;
        }
    }
    // Handle invalid input (not in the predefined list)
    while (ranges::find(handednessList.begin(),handednessList.end(),dominantHandInput) == handednessList.end()) {
        cout << "Please type your handedness (right/left/both)"<< endl;
        cin >> dominantHandInput;
    }
    this->dominantHand = dominantHandInput;
}

// WIP : define the passphrase part