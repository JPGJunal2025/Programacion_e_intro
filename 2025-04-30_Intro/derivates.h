#pragma once

#include <functional>
#include <cmath>

using fptr = std::function<double(double)>;

double deriv_central(fptr f, double x, double h);
double deriv_forward(fptr f, double x, double h);

// notice the fptr inside the algptr
using algptr = std::function<double(fptr, double, double)>;

double richardson(fptr f, double x, double h, algptr alg, int n); // n is the algorithm order