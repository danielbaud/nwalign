#pragma once
#include <string>
#include <iostream>


using namespace std;

class Parser {

public:
    Parser();
    bool parse(int argc, char **argv);
    void help(char *name) const;

    string cmd;
    string x;
    string y;
    double e;
    double o;

};