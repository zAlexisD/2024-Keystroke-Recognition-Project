cmake_minimum_required(VERSION 3.30)
project(3A_RTS_miniProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(3A_RTS_miniProject main.cpp
        KeyEventsHandling.cpp
        KeyEventsHandling.h
        myKeystrokeDB.cpp
        mainTest.cpp
        InterfaceKbdDB.cpp
        InterfaceKbdDB.h
)
