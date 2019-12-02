#include "parser.hh"

Parser::Parser() : cmd("") , x("") , y("") , e(-1) , o(0)
{}


bool Parser::parse(int argc, char **argv) {
    if (argc < 4 || argc > 5) {
        this->help(argv[0]);
        return false;
    }
    int d = 0;
    if (argc == 5) {
        d = 1;
        string gamma = argv[1];
        string prefix = "--gamma=";
        if (gamma.substr(0, prefix.size()) != prefix) {
            this->help(argv[0]);
            return false;
        }
        string eo = gamma.substr(prefix.size(), gamma.size() - prefix.size());
        size_t split = eo.find(",");
        if (split == string::npos) {
            this->help(argv[0]);
            return false;
        }
        this->e = stof(eo.substr(0, split));
        this->o = stof(eo.substr(split+1, eo.size()));
    }
    this->cmd = argv[1 + d];
    this->x = argv[2 + d];
    this->y = argv[3 + d];
    return true;
}

void Parser::help(char *name) const {
    cerr << "Usage:" << endl;
    cerr << "\t" << name << " [ --gamma=e,o ] cmd x y" << endl;
}