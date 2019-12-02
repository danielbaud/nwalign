#include "sequence.hh"

Sequence::Sequence(const string& seq) {
    this->sequence = seq;
    this->type = UNKNOWN;
    bool isDna = true;
    bool isRna = true;
    bool isProt = true;
    for (unsigned i = 0; i < seq.size(); ++i) {
        char c = seq[i];
        if (this->dna.find(c) == this->dna.end())
            isDna = false;
        if (this->rna.find(c) == this->rna.end())
            isRna = false;
        if (this->prot.find(c) == this->prot.end())
            isProt = false;
    }
    if (isDna)
        this->type = (SequenceType)(this->type + DNA);
    if (isRna)
        this->type = (SequenceType)(this->type + RNA);
    if (isProt)
        this->type = (SequenceType)(this->type + PROT);
}

string Sequence::get_sequence() const {
    return this->sequence;
}

SequenceType Sequence::get_type() const {
    return this->type;
}