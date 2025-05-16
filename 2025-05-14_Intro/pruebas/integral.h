#pragma once
#include <cmath>
#include <functional>

// Integrales
using fptr = std::function<double(double)>;

// trapezoid(0.0, 1.0, 10, fun)
double trapezoid(double a, double b, int N, fptr fun);

double simpson(double a, double b, int N, fptr fun);

using intgptr = std::function<double(double, double, int, fptr)>;

double richardson_integral(double a, double b, int N, fptr f, intgptr, int alpha);

 /*Derivadas
double forward_diff(double x, double h, fptr f);
double central_diff(double x, double h, fptr f);*/