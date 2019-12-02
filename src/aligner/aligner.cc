#include "aligner.hh"
#include "sequence.hh"

Aligner::Aligner(const string& x, const string& y, double e, double o) :
x(Sequence(x)), y(Sequence(y)), st(UNKNOWN), e(e), o(o)
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
    if (rna || dna)
        this->st = (SequenceType)(DNA | RNA);
    else
        this->st = PROT;
    return true;
}


bool Aligner::score() const {
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