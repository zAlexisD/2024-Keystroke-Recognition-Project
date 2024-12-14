//
// Created by alexisd on 12/12/24.
//
#include "InterfaceKbdDB.h"
#include "KeyEventsHandling.h"

int main() {
    // Keyboard initiation
    string device_path = getKeyboardPath();
    libevdev* dev = initDevice(device_path);

    // Initiate the User session to get their information
    UserID userID;
    userID.gatherInformation();

    // Check infos
    cout << "\n---------- Let's now check the information gathered ----------\n" << endl;
    userID.displayUserID();

    // Main loop
    cout << "\n---------- It's time to tytytyty-tyyyyyype the passphrase----------\n" << endl;
    const auto timeData = getUserData(userID,dev);

    // Save data in a file
    saveCsvData(userID,timeData);

    // Clean up and free the libevdev struct.
    libevdev_free(dev);
    return EXIT_SUCCESS;
}