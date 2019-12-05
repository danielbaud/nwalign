#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "sequence.hh"

using namespace std;

class Aligner {
public:
    Aligner(const string& x, const string& y, double e, double o);
    bool checkSequencesType(char *name);
    bool parseMatrix(string path);
    double gamma(double x) const;
    bool score();
    bool align();

private:
    Sequence x;
    Sequence y;
    SequenceType st;
    double e;
    double o;
    map<char, map<char, int>> matrix;
};
