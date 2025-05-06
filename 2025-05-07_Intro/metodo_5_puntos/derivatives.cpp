#include "derivatives.h"

double forward_diff(double x, double h, fptr f) {
    return (f(x + h) - f(x)) / h;
}
double central_diff(double x, double h, fptr f) {
    return (f(x + h) - f(x - h)) / (2*h);
}
double five_point_diff(double x, double h, double (*f)(double)) {
    return (-f(x + 2*h) + 8*f(x + h) - 8*f(x - h) + f(x - 2*h)) / (12 * h);
}

