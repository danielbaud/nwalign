#include "utils.hh"

double max3(double a, double b, double c) {
    double d = a > b ? a : b;
    return c > d ? c : d;
}

double argmax3(double a, double b, double c) {
    double r = max3(a, b, c);
    if (r == a)
        return 0;
    if (r == b)
        return 1;
    return 2;
}