# --- Makefile ---

CXX = g++
CXXFLAGS = -Wall -Wextra -g
SRC = $(wildcard *.cpp resources/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q *.o resources\*.o $(TARGET).exe 2>nul || true
