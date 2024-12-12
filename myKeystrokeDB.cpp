//
// Created by alexisd on 12/12/24.
//
#include "KeyEventsHandling.h"

int main() {
    // Inits
    string passphrase = "example passphrase";
    // Keyboard initiation
    string device_path = getKeyboardPath();
    libevdev* dev = initDevice(device_path);

    cout << "\nPlease type '" << passphrase << "' and press Enter to finish : " << endl;

    // Capture keyboard events and collect timing data
    auto timeMeasure = captureKeyboardEvents(dev);

    // Conversion to have interpretable data
    auto timeMeasureData = timeToInt(timeMeasure);

    // ----- Debug -----
    // output of collected timing data
    cout << "\n---------- Collected Timing data ----------\n";
    // define temporary header for the vector
    vector<string> feature_name = {
    "Time between two key presses",
    "Time between two key releases",
    "Time between release and press",
    "Time between press and release"
    };
    // Display the time measures
    cout << "\n----- Time measures -----\n";
    for (size_t i = 0; i < timeMeasure.size(); ++i) {
        cout << feature_name[i] << " : \n";
        for (const auto& value : timeMeasure[i]) {
            cout << value << "µs ";
        }
        cout << endl;
    }
    // Display the time measure in ML data format
    cout << "\n----- Corresponding Time Data -----\n";
    for (size_t i = 0; i < timeMeasureData.size(); ++i) {
        cout << feature_name[i] << " : \n";
        for (const auto& value : timeMeasureData[i]) {
            cout << value << " ";
        }
        cout << endl;
    }
    // Clean up and free the libevdev struct.
    libevdev_free(dev);
    return EXIT_SUCCESS;
}