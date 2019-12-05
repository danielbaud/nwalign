CXX = g++
CXXFLAGS = -Werror -Wall -Wextra -pedantic -std=c++17

SRC = src/parser/parser.cc src/aligner/aligner.cc \
		src/aligner/aligner_common.cc src/aligner/sequence.cc \
		src/utils/utils.cc src/main.cc

SRC_SIMPLE = src/parser/parser.cc src/aligner/aligner \
		src/aligner/aligner_simple.cc src/aligner/sequence.cc \
		src/utils/utils.cc src/main.cc

TARGET = nwalign

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) -g -DPATH=\"$$PWD\"

$(TARGET)_simple: $(SRC_SIMPLE)
	$(CXX) $(CXXFLAGS) $(SRC_SIMPLE) -o $(TARGET) -g -DPATH=\"$$PWD\"

clean:
	rm -rf $(TARGET)

test:
	tests/testsuite.sh
