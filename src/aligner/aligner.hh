#pragma once
#include <string>
#include <iostream>
#include <list>
#include "sequence.hh"

using namespace std;

class Aligner {
public:
    Aligner(const string& x, const string& y, double e, double o);
    bool checkSequencesType(char *name);
    bool score() const;
    bool align() const;

private:
    Sequence x;
    Sequence y;
    SequenceType st;
    double e;
    double o;
};
