CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
SRC = $(wildcard *.cpp resources/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(TARGET).exe 2>nul
