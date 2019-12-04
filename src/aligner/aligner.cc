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
        this->parseMatrix("matrices/dna.mat");
    }
    else if (rna) {
        this->st = RNA;
        this->parseMatrix("matrices/rna.mat");
    }
    else if (prot) {
        this->st = PROT;
        this->parseMatrix("matrices/blosum62.mat");
    }
    else {
        cerr << name << ": Sequences are not of the same type" << endl;
        return false;
    }
    return true;
}

void Aligner::parseMatrix(string path) {
    string P = PATH;
    ifstream file(P + '/' + path);
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
    vector<vector<double>> s = vector<vector<double>>(l1 + 1, vector<double>(l2 + 1));
    for (unsigned i = 0; i <= l1; ++i)
        s[i][0] = this->gamma(i);
    for (unsigned i = 0; i <= l2; ++i)
        s[0][i] = this->gamma(i);
    for (unsigned i = 1; i <= l1; ++i) {
        for (unsigned j = 1; j <= l2; ++j) {
            double max_i = this->gamma(1) + s[i-1][j];
            for (unsigned k = 2; k <= i; k++) {
                double temp = this->gamma(k) + s[i-k][j];
                if (temp > max_i)
                    max_i = temp;
            }
            double max_j = this->gamma(1) + s[i][j-1];
            for (unsigned k = 2; k <= j; k++) {
                double temp = this->gamma(k) + s[i][j-k];
                if (temp > max_j)
                    max_j = temp;
            }
            s[i][j] = max3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], max_i, max_j);
        }
    }
    printf("%.1f\n", s[l1][l2]);
    return true;
}

bool Aligner::align() {
    string seq1 = this->x.get_sequence();
    string seq2 = this->y.get_sequence();
    unsigned l1 = seq1.size();
    unsigned l2 = seq2.size();
    vector<vector<double>> s = vector<vector<double>>(l1 + 1, vector<double>(l2 + 1));
    vector<vector<pair<unsigned, unsigned>>> b = vector<vector<pair<unsigned, unsigned>>>(l1 + 1, vector<pair<unsigned, unsigned>>(l2 + 1, {0, 0}));
    for (unsigned i = 0; i <= l1; ++i) {
        s[i][0] = this->gamma(i);
        b[i][0] = pair<unsigned, unsigned>(0, 0);
    }
    for (unsigned i = 0; i <= l2; ++i) {
        s[0][i] = this->gamma(i);
        b[0][i] = pair<unsigned, unsigned>(0, 0);
    }
    for (unsigned i = 1; i <= l1; ++i) {
        for (unsigned j = 1; j <= l2; ++j) {
            double max_i = this->gamma(1) + s[i-1][j];
            int k_i = 1;
            for (unsigned k = 2; k <= i; k++) {
                double temp = this->gamma(k) + s[i-k][j];
                if (temp > max_i) {
                    max_i = temp;
                    k_i = k;
                }
            }
            double max_j = this->gamma(1) + s[i][j-1];
            int k_j = 1;
            for (unsigned k = 2; k <= j; k++) {
                double temp = this->gamma(k) + s[i][j-k];
                if (temp > max_j) {
                    max_j = temp;
                    k_j = k;
                }
            }
            s[i][j] = max3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], max_i, max_j);
            int index = argmax3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], max_i, max_j);
            if (index == 0) {
                b[i][j] = pair(i-1, j-1);
            } else if (index == 1) {
                b[i][j] = pair(i-k_i, j);
            } else {
                b[i][j] = pair(i, j-k_j);
            }
        }
    }
    string res1 = "";
    string res2 = "";
    do {
        pair<unsigned, unsigned> p = b[l1][l2];
        unsigned d_i = l1 - p.first;
        unsigned d_j = l2 - p.second;
        if (d_i == d_j) {
            for (unsigned i = 0; i < d_i; ++i) {
                res1 = seq1[l1-i-1] + res1;
                res2 = seq2[l2-i-1] + res2;
            }
        }
        else {
            if (d_i > 0 && d_j > 0)
                return false;
            for (unsigned i = 0; i < d_i; ++i) {
                res1 = seq1[l1-i-1] + res1;
                res2 = '-' + res2;
            }
            for (unsigned i = 0; i < d_j; ++i) {
                res1 = '-' + res1;
                res2 = seq2[l2-i-1] + res2;
            }
        }
        l1 = p.first;
        l2 = p.second;        
    } while (l1 > 0 || l2 > 0);
    cout << res1 << endl;
    cout << res2 << endl;
    return true;
}