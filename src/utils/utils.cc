#include "utils.hh"

double max3(double a, double b, double c) {
    double d = a > b ? a : b;
    return c > d ? c : d;
}

double argmax3(double a, double b, double c) {
    double ret = 0;
    double d = a > b ? a : b;
    ret = d == a ? 0 : 1;
    d = c > d ? c : d;
    return d == c ? 2 : ret;
}