CXX = g++
CXXFLAGS = -Werror -Wall -Wextra -pedantic -std=c++17

SRC = src/parser/parser.cc src/aligner/aligner.cc \
		src/aligner/sequence.cc src/main.cc
TARGET = nwalign

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)

test:
	tests/testsuite.sh
