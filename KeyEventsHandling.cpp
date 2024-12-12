//
// Created by alexisd on 11/12/24.
//

#include "KeyEventsHandling.h"

// Function to help user retrieving their keyboard event path
string getKeyboardPath() {
    // Inits
    string event_number;
    // Help guide
    cout << " ----- Hey, let's first setup the program with your keyboard -----" << endl;
    cout << "1 -> Please check on a terminal : ls /dev/input/by-id/ or ls /dev/input/by-path/" << endl;
    cout << "2 -> Find the device finishing with -kbd, it's the link to your keyboard." << endl;
    cout << "3 -> Then, to find the associated event type : readlink /dev/input/by-path/<yourKeyboardLink>" << endl;
    cout << "To which eventX is it linked ?" << endl;
    cin >> event_number;
    // Output
    string device_path = "/dev/input/"+event_number;
    return device_path;
}

// Initiate the device
libevdev* initDevice(const string& device_path) {
    // Inits and open the device
    libevdev* dev = nullptr;
    int fd = open(device_path.c_str(), O_RDONLY | O_NONBLOCK);

    // Handle errors
    if (fd < 0) {
        perror("Failed to open device");
        exit(EXIT_FAILURE);
    }
    if (libevdev_new_from_fd(fd, &dev) < 0) {
        perror("Failed to initialize libevdev");
        exit(EXIT_FAILURE);
    }

    // Output
    cout << "Device initialised : " << libevdev_get_name(dev) << endl;
    return dev;
}

// Get the current timestamp in microseconds
chrono::time_point<chrono::steady_clock>getCurrentTime() {
    return chrono::steady_clock::now();
}

// Compute the time difference in microseconds
double computeDuration(const chrono::time_point<chrono::steady_clock>& start,const chrono::time_point<chrono::steady_clock>& end) {
    return chrono::duration_cast<chrono::duration<double>>(end - start).count();
}

// Now let's handle key press and release, and store timing data
vector<vector<double>> captureKeyboardEvents(libevdev* dev) {
    // Inits
    input_event event;
    vector<vector<double>> timeMeasure(nb_features);
    bool first_key_press = true,first_key_release = true;
    // Variables to store the last press/release times initiated as empty timestamps
    auto start_time = chrono::time_point<chrono::steady_clock>();
    auto last_press_time = start_time;
    auto last_release_time = start_time;

    // Listening mode
    while(true) {
        int rc = libevdev_next_event(dev,LIBEVDEV_READ_FLAG_NORMAL,&event);
        if (rc == LIBEVDEV_READ_STATUS_SUCCESS) {
            auto current_time = getCurrentTime();

            // "Enter" key pressed notifies that the user finished typing and end the event listening mode
            if (event.type == EV_KEY && event.value == 1 && event.code == KEY_ENTER) {
                // maybe add the total time as a feature ? don't know if it is relevant
                auto end_time = current_time;
                double duration = computeDuration(start_time, end_time);
                cout << "\nTyping duration : " << duration << endl;
                break;
            }

            // Detect other key events
            if (event.type == EV_KEY) {
                // Key press case (value = 1)
                if (event.value == 1) {
                    // Handle the moment the user starts typing : first key press
                    if (first_key_press) {
                        start_time = current_time;
                        last_press_time = current_time;
                        first_key_press = false;
                    } else {
                        // Feature 1 : Time between two key presses
                        timeMeasure[0].push_back(computeDuration(last_press_time, current_time));
                        last_press_time = current_time; // Update the new press time

                        // Feature 3 : Time between a release and a press
                        timeMeasure[2].push_back(computeDuration(last_release_time, current_time));
                    }
                }
                // Key release case (value = 0)
                else if (event.value == 0) {
                    // Handle the moment the user starts typing : first key release
                    if (first_key_release) {
                        last_release_time = current_time;
                        first_key_release = false;
                    } else {
                        // Feature 2 : Time between two key releases
                        timeMeasure[1].push_back(computeDuration(last_release_time, current_time));
                        last_release_time = current_time;

                        // Feature 4 : Time between a press and a release
                        timeMeasure[3].push_back(computeDuration(last_press_time, current_time));
                    }
                }
            }
        }
    }
    return timeMeasure;
}

// Convert the time measures into interpretable data for Machine Learning
vector<vector<int>> timeToInt(vector<vector<double>> timeMeasure) {
    // Init
    double multiplier = 1e8;
    vector<vector<int>> timeMeasureInt;
    // Double for loop to parkour each element
    for (const auto& innerVector : timeMeasure) {
        vector<int> timeMeasureInt_row;
        for (double element : innerVector) {
            // Multiply each element by 10^8 and take the integer part
            int element_int = static_cast<int>(element * multiplier);
            timeMeasureInt_row.push_back(element_int);
        }
        // Add the row to the resulted vector
        timeMeasureInt.push_back(timeMeasureInt_row);
    }
    return timeMeasureInt;
}