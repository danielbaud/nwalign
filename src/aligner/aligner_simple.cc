#include "aligner.hh"
#include "sequence.hh"
#include "../utils/utils.hh"


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
        s[i][0] = i * this->e;
    for (unsigned i = 0; i <= l2; ++i)
        s[0][i] = i * this->e;
    for (unsigned i = 1; i <= l1; ++i) {
        for (unsigned j = 1; j <= l2; ++j) {
            s[i][j] = max3(this->matrix[seq1[i-1]][seq2[j-1]] + s[i-1][j-1], this->e + s[i-1][j], this->e + s[i][j-1]);
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