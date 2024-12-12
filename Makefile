# Define compiler and flags (we use c++ version 20 on g++ vers 13.2.0)
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

# Linker flags to include libevdev
LDFLAGS = -levdev

# Output executable name
TARGET = keystrokeDB

# Source files and object files
SRCS = myKeystrokeDB.cpp KeyEventsHandling.cpp InterfaceKbdDB.cpp
OBJS = $(SRCS:.cpp=.o)

# Header file
HEADERS = KeyEventsHandling.h InterfaceKbdDB.h

# Default target: build the program
all: $(TARGET)

# Link object files into the final executable, with libevdev
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the generated files (object files, executable, etc.)
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# As we need to use sudo with the libevdev library, we won't need this part
# Make the program executable directly
#run: $(TARGET)
#	./$(TARGET)
