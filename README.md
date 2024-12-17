# User Identification via Keystroke 
3rd year RTS mini project at ENSEA

## Objectives

## Overview

## Dependencies
Versions :
- C++20
- Compiler g++ 13.2.0

For now, it works only on Linux distribution because of the use of the `libevdev` library and the location of the devices events directory

## Usage
1- Make sure to have the Makefile, the`.cpp` and `.h` files in the current directory

2- Command `make` to compile the code

3- you should have an executable `keystrokeDB`, execute it with :
```bash
sudo ./keystrokeDB
```
Note : The `libevdev` library needs to be run as root.

4- Command `make clean` to delete the `.o` files and the executable or directly use `make clean all è if you want to delete all and recompile directly.

## WIP
- Extend the use to Windows + MacOS users -> make a crossplateform version for easy use (web ?)
- Handle users with same name
- Handle the errors
- Make a graphical user interface (GUI)
- Add the Python code part
- Some small fixes
- Concatenate the different passphrase to have one single study