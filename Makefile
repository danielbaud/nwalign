CXX = g++
CXXFLAGS = -Werror -Wall -Wextra -pedantic -std=c++17

SRC = src/parser/parser.cc src/main.cc
TARGET = nwalign

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)
