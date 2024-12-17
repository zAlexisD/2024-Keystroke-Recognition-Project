//
// Created by alexisd on 12/12/24.
//

#include "InterfaceKbdDB.h"
#include "KeyEventsHandling.h"

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
void UserID::setParameter(T UserID::*attribute,const T& paramInterface,const vector<string>& paramList){
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
    cout << "\nWhat is your name?"<< endl;
    cin >> usernameInput;
    // Handle non-valid username case = empty entry
    // WIP : not very well handled but still works
    // WIP : handle composed name
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
// Gather all the previous methods in one call
void UserID::gatherInformation() {
    setUsername();
    setGender();
    setDominantHand();
    setPassphrase();
}

// Display attributes method
void UserID::displayUserID() const {
    cout << "Username: " << username << endl;
    cout << "Gender: " << gender << endl;
    cout << "Dominant hand: " << dominantHand << endl;
    cout << "Choice of passphrase to type : " << passphrase << endl;
}

// Ask user to type the chosen passphrase N times, get data and store in a file
vector<vector<int>> getUserData(UserID userSettings,libevdev* dev) {
    // Inits
    int attempts = 0;
    vector<vector<int>> userData(maxPassphraseAttempt);
    //
    cout << "\nThe passphrase to type " << maxPassphraseAttempt << " times is: " << userSettings.getPassphrase() << endl;
    // Main loop
    while (attempts < maxPassphraseAttempt) {
        attempts++;
        cout << "\nAttempt: " << attempts <<"/"<< maxPassphraseAttempt << endl;
        cout << "Please type '" << userSettings.getPassphrase() << "' and press Enter to finish" << endl;
        KeyCapture timeCapture = captureKeyboardEvents(dev);
        // If error detected in the passphrase typed, do it again
        if (timeCapture.getUserInput() != userSettings.getPassphrase()) {
            timeCapture.resetCapture();
            attempts--;
            cout << "\nWrong passphrase! Try again please :)\n";
        }
        else {
            // Convert the time Measures into 1-row of interpretable data
            const vector<int> timeData = timeToData(timeCapture.getTimeMeasure());
            // Copy the data row in keyboardData
            userData[attempts-1] = timeData;
        }
    }
    return userData;
}

// Generate the header for the csv file according to the number of characters of the passphrase
vector<string> genCsvHeader(UserID userID) {
    // Init
    const int passphraseSize = static_cast<int>(userID.getPassphrase().size());
    vector<string> csvHeader;
    // First add the 3 attributes of the users
    const string userAttributes = "User,Gender,Handedness,";
    csvHeader.push_back(userAttributes);
    // Define for each feature the header : nb_characters-1 columns
    for (int feature = 1; feature <= nb_features; feature++) {
        for (int featureCol = 1; featureCol <= passphraseSize-1; featureCol++) {
            ostringstream oss;
            // Format : "Feature<i>_<j>"
            oss << "Feature" << feature << "_" << featureCol;
            // Handle separation
            if (featureCol != passphraseSize-1) {
                oss << ",";
            }
            csvHeader.push_back(oss.str());
        }
    }
    // Go back to line for the data
    csvHeader.push_back("\n");
    return csvHeader;
}

// Store the data in csv format, add header and save file in /myData directory
void saveCsvData(UserID userSettings,vector<vector<int>> userData) {
    // Inits
    string passphraseSize;
    // WIP : Handle this cleaner ?
    if (userSettings.getPassphrase() == "donut sucre") {
        passphraseSize = "short";
    }
    else if (userSettings.getPassphrase() == "we want a mid passphrase") {
        passphraseSize = "medium";
    }
    else if (userSettings.getPassphrase() == "rts stands for network telecommunications and security") {
        passphraseSize = "long";
    }
    // Define the file path and its name
    const string filename = userSettings.getUsername()+"_"+passphraseSize+".csv";
    const string filepath = "./myData/"+filename;
    // Saving file settings
    ofstream output_file(filepath);
    // Init the file with the header
    vector<string> csvHeader = genCsvHeader(userSettings);
    for (const auto& headerCol : csvHeader) {
        output_file << headerCol;
    }
    // Copy the data in the file
    for (size_t row = 0; row < userData.size(); row++) {
        // First add on each row the user's information
        output_file << userSettings.getUsername() << "," << userSettings.getGender() << "," << userSettings.getDominantHand() << ",";
        // Then add the content of each row
        for (size_t col = 0; col < userData[row].size(); col++) {
            output_file << userData[row][col];
            // Separate data by a coma if it's not the last element of the row
            if (col != userData[row].size() - 1) {
                output_file << ",";
            }
        }
        // After each row, go to newline
        output_file << endl;
    }
    cout << "\nThank you for your participation !!! You can find the data file in " << filepath << endl;
}