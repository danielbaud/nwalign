#include <iostream>
#include "parser/parser.hh"

int main(int argc, char **argv) {
    Parser p = Parser();
    if (!p.parse(argc, argv))
        return 1;
    cout << "cmd: " << p.cmd << endl;
    cout << "x: " << p.x << endl;
    cout << "y: " << p.y << endl;
    cout << "e: " << p.e << endl;
    cout << "o: " << p.o << endl;
    return 0;
}