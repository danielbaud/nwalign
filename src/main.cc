#include <iostream>
#include "parser/parser.hh"
#include "aligner/aligner.hh"

int main(int argc, char **argv) {
    Parser p = Parser();
    if (!p.parse(argc, argv))
        return 1;
    Aligner aligner = Aligner(p.x, p.y, p.e, p.o);
    if (!aligner.checkSequencesType(argv[0]))
        return 1;
    if (p.cmd == "score"){
        if (!aligner.score())
            return 1;
    }
    else if (p.cmd == "align") {
        if (!aligner.align())
            return 1;
    }
    else {
        cerr << argv[0] << ": cmd must be either 'score' or 'align'" << endl;
        return 1;
    }
    return 0;
}