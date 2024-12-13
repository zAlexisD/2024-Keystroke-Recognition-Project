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
string UserID::getPassphrase() {
    return passphrase;
}

// Method for setters structure on all attributes except username
template <typename T>
void UserID::setParameter(T UserID::*attribute,const T& paramInterface,const vector<const string>& T& paramList){
    // Init
    string userInput;
    // User prompt input
    cout << "What is your " << paramInterface << " ?"<< endl;
    cin >> userInput;
    // Handle empty entry
    // Note : empty() returns true if the vector or string is empty
    if (userInput.empty()) {
        while(userInput.empty()){
            cout << "Please type your " << paramInterface << endl;
            cin >> userInput;
        }
    }
    // Handle invalid input (not in the predefined list)
    // Note : find() returns an iterator to the found element in the range of a vector
    // it returns an iterator to vector.end() if the element is not found
    while (ranges::find(paramList.begin(), paramList.end(), userInput) == paramList.end()) {
        cout << "Please type your " << paramInterface << endl;
        cin >> userInput;
    }
    // Assign the user input to the corresponding attribute
    this->*attribute = userInput;
}


// UserID class setters
void UserID::setUsername() {
    // Init
    string usernameInput;
    // User prompt input
    cout << "Hello ! What is your name?"<< endl;
    cin >> usernameInput;
    // Handle non-valid username case = empty entry
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
    const string genderParam = "gender (male,female,other)";
    // Call the template
    setParameter(&UserID::gender,genderParam,genderList);
}
void UserID::setDominantHand() {
    // Init
    const string dominantHandParam = "dominant hand (right,left,both)";
    // Call the template
    setParameter(&UserID::dominantHand,dominantHandParam,handednessList);
}
void UserID::setPassphrase() {
    // Init
    const string choiceParam = "choice of passphrase (short,medium,long)";
    // Call the template
    setParameter(&UserID::passphrase,choiceParam,passphraseChoice);
    // Set real passphrase to the attribute according to the user's choice
    if (passphrase == "short" || passphrase == "s") {
        this->passphrase = passphraseList[0];
    }
    else if (passphrase == "medium" || passphrase == "m") {
        this->passphrase = passphraseList[1];
    }
    else {
        this->passphrase = passphraseList[2];
    }
}
// WIP : display method
// WIP : define the passphrase part