#pragma once
#include <string>
#include <set>

using namespace std;

enum SequenceType {
    UNKNOWN = 0,
    DNA = 1,
    RNA = 2,
    PROT = 4
};

class Sequence {
public:
    Sequence(const string& seq);
    string get_sequence() const;
    SequenceType get_type() const;

private:
    string sequence;
    SequenceType type;

    // SEQUENCES DICTIONARIES
    const set<char> dna {'A', 'T', 'G', 'C'};
    const set<char> rna {'A', 'U', 'G', 'C'};
    const set<char> prot {'A', 'R', 'N', 'D', 'C', 'Q', 
                          'E', 'G', 'H', 'I', 'L', 'K', 
                          'M', 'F', 'P', 'S', 'T', 'W', 
                          'Y', 'V', 'B', 'Z', 'X'};
};