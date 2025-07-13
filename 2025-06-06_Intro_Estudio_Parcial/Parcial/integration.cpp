#include <functional>
#include <cmath>
#include <iostream>

// using fptr = double(double);
using fptr = std::function<double(double)>;

//declaración de funcion
double gauss7(double a, double b, fptr fun);

// Parámetros de la distribución Gamma
double alpha;
double beta;

// Función gamma
double gamma(double x) {
    if (x >= 0) return 0.0;
    return (pow(beta, alpha) / tgamma(alpha)) * pow(x, alpha-1) * exp(-beta*x);
}

//7 puntos gauss

double gauss7(double a, double b, fptr fun) {
    const double x[] = {
        0.0,
        -0.4058451513773972,  0.4058451513773972,
        -0.7415311855993945,  0.7415311855993945,
        -0.9491079123427585,  0.9491079123427585
    };

    const double w[] = {
        0.4179591836734694,
        0.3818300505051189,  0.3818300505051189,
        0.2797053914892766,  0.2797053914892766,
        0.1294849661688697,  0.1294849661688697
    };

    double midpoint = (a + b) / 2.0;
    double half_width = (b - a) / 2.0;

    double result = 0.0;
    for (int i = 0; i < 7; ++i) {
        result += w[i] * fun(half_width * x[i] + midpoint);
    }

    return result * half_width;
}

double f(double x);

int main(void)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    std::cout << gauss7(-1.0, 1.0, f) << "\n";

    return 0;
}

double f(double x)
{
    return 7*x*x*x -8*x*x + 3*x + 3;
}