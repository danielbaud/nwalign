#include <fstream>
#include "aligner.hh"
#include "sequence.hh"

Aligner::Aligner(const string& x, const string& y, double e, double o) :
x(Sequence(x)), y(Sequence(y)), st(UNKNOWN), e(e), o(o), matrix({})
{}

bool Aligner::checkSequencesType(char *name) {
    SequenceType x_type = this->x.get_type();
    SequenceType y_type = this->y.get_type();
    if (x_type == UNKNOWN || y_type == UNKNOWN) {
        cerr << name << ": Sequence type is not valid" << endl;
        return false;
    }
    bool dna = (x_type & DNA) && (y_type & DNA);
    bool rna = (x_type & RNA) && (y_type & RNA);
    bool prot = (x_type & PROT) && (y_type & PROT);
    if (!dna && !rna && !prot) {
        cerr << name << ": Sequences are not of the same type" << endl;
        return false;
    }
    if (rna || dna) {
        this->st = (SequenceType)(DNA | RNA);
        this->parseMatrix("matrices/nucleic.mat");
    }
    else {
        this->st = PROT;
        this->parseMatrix("matrices/blosum62.mat");
    }
    return true;
}

void Aligner::parseMatrix(string path) {
    ifstream file(path);
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
}

double Aligner::gamma(double x) const {
    return (this->e * x) + this->o;
}


bool Aligner::score(){
    cout << this->matrix['n']['n'] << endl;
    cout << "Score with:" << endl;
    cout << "\tx = " << this->x.get_sequence() << endl;
    cout << "\ty = " << this->y.get_sequence() << endl;
    cout << "\te = " << this->e << endl;
    cout << "\to = " << this->o << endl;
    return true;
}

bool Aligner::align() const {
    cout << "Align with:" << endl;
    cout << "\tx = " << this->x.get_sequence() << endl;
    cout << "\ty = " << this->y.get_sequence() << endl;
    cout << "\te = " << this->e << endl;
    cout << "\to = " << this->o << endl;
    return true;
}