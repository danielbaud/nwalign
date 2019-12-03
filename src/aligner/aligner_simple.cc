#include <fstream>
#include "aligner.hh"
#include "sequence.hh"
#include "../utils/utils.hh"

Aligner::Aligner(const string& x, const string& y, double e, double o) :
x(Sequence(x)), y(Sequence(y)), st(UNKNOWN), e(e), o(o), matrix({})
{}

bool Aligner::checkSequencesType(char *name) {
    if (e < 0 || o < 0) {
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


bool Aligner::score() {
    string seq1 = this->x.get_sequence();
    string seq2 = this->y.get_sequence();
    unsigned l1 = seq1.size();
    unsigned l2 = seq2.size();
    vector<vector<int>> s = vector<vector<int>>(l1 + 1, vector<int>(l2 + 1));
    for (unsigned i = 0; i <= l1; ++i)
        s[i][0] = i * this->e;
    for (unsigned i = 0; i <= l2; ++i)
        s[0][i] = i * this->e;
    for (unsigned i = 1; i <= l1; ++i) {
        for (unsigned j = 1; j <= l2; ++j) {
            s[i][j] = max3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], this->e + s[i-1][j], this->e + s[i][j-1]);
        }
    }
    cout << s[l1][l2] << endl;
    return true;
}

bool Aligner::align() {
    string seq1 = this->x.get_sequence();
    string seq2 = this->y.get_sequence();
    unsigned l1 = seq1.size();
    unsigned l2 = seq2.size();
    vector<vector<int>> s = vector<vector<int>>(l1 + 1, vector<int>(l2 + 1));
    vector<vector<pair<unsigned, unsigned>>> b = vector<vector<pair<unsigned, unsigned>>>(l1 + 1, vector<pair<unsigned, unsigned>>(l2 + 1, {0, 0}));
    for (unsigned i = 0; i <= l1; ++i) {
        s[i][0] = i * this->e;
        b[i][0] = pair<unsigned, unsigned>({i-1, 0});
    }
    for (unsigned i = 0; i <= l2; ++i) {
        s[0][i] = i * this->e;
        b[0][i] = pair<unsigned, unsigned>({0, i-1});
    }
    for (unsigned i = 1; i <= l1; ++i) {
        for (unsigned j = 1; j <= l2; ++j) {
            s[i][j] = max3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], this->e + s[i-1][j], this->e + s[i][j-1]);
            int index = argmax3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], this->e + s[i-1][j], this->e + s[i][j-1]);
            if (index == 0) {
                b[i][j] = pair(i-1, j-1);
            } else if (index == 1) {
                b[i][j] = pair(i-1, j);
            } else {
                b[i][j] = pair(i, j-1);
            }
        }
    }
    string res1 = "";
    string res2 = "";
    do {
        pair<unsigned, unsigned> p = b[l1][l2];
        if (p.first == l1 - 1)
            res1 = seq1[l1-1] + res1;
        else
            res1 = '-' + res1;
        if (p.second == l2 - 1)
            res2 = seq2[l2-1] + res2;
        else
            res2 = '-' + res2;
        l1 = p.first;
        l2 = p.second;        
    } while (l1 > 0 || l2 > 0);
    cout << res1 << endl;
    cout << res2 << endl;
    return true;
}