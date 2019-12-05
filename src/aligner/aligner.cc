#include <fstream>
#include "aligner.hh"
#include "sequence.hh"
#include "../utils/utils.hh"
#ifndef PATH
#define PATH "."
#endif

Aligner::Aligner(const string& x, const string& y, double e, double o) :
x(Sequence(x)), y(Sequence(y)), st(UNKNOWN), e(e), o(o), matrix({})
{}

bool Aligner::checkSequencesType(char *name) {
    if (e > 0 || o > 0) {
        cerr << name << ": gamma values e and o must be <= 0" << endl;
        return false;
    }
    SequenceType x_type = this->x.get_type();
    SequenceType y_type = this->y.get_type();
    if (x_type == UNKNOWN || y_type == UNKNOWN) {
        cerr << name << ": Sequence type is not valid" << endl;
        return false;
    }
    bool dna = (x_type & DNA) && (y_type & DNA);
    bool rna = (x_type & RNA) && (y_type & RNA);
    bool prot = (x_type & PROT) && (y_type & PROT);
    if (dna) {
        this->st = DNA;
        return this->parseMatrix("matrices/dna.mat");
    }
    else if (rna) {
        this->st = RNA;
        return this->parseMatrix("matrices/rna.mat");
    }
    else if (prot) {
        this->st = PROT;
        return this->parseMatrix("matrices/blosum62.mat");
    }
    cerr << name << ": Sequences are not of the same type" << endl;
    return false;
}

bool Aligner::parseMatrix(string path) {
    string P = PATH;
    ifstream file(P + '/' + path);
    if (!file.is_open()) {
        cerr << "Matrix file not found at " << P + '/' + path << ". Are you sure it exists?" << endl;
        cerr << "Try recompiling at new location" << endl;
        return false;
    }
    unsigned size;
    file >> size;
    vector<char> keys = {};
    for (unsigned i = 0; i < size; ++i) {
        char c;
        file >> c;
        keys.push_back(c);
    }
    for (unsigned i = 0; i < size; ++i) {
        map<char, int> current = {};
        int temp;
        for (unsigned j = 0; j < size; ++j) {
            file >> temp;
            current.insert(pair<char, int>(keys[j], temp));
        }
        this->matrix.insert(pair<char, map<char, int>>(keys[i], current));
    }
    return true;
}