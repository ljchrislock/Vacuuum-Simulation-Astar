# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Target executable
TARGET = vacuum_simulation

# Source files and object files
SRCS = main.cpp Grid.cpp Vacuum.cpp AStar.cpp
OBJS = main.o Grid.o Vacuum.o AStar.o

# Default target
all: $(TARGET)

# Build the target executable by linking object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp file into a .o file
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Grid.o: Grid.cpp
	$(CXX) $(CXXFLAGS) -c Grid.cpp -o Grid.o

Vacuum.o: Vacuum.cpp
	$(CXX) $(CXXFLAGS) -c Vacuum.cpp -o Vacuum.o

AStar.o: AStar.cpp
	$(CXX) $(CXXFLAGS) -c AStar.cpp -o AStar.o

# Clean the build
clean:
	del /Q *.o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
