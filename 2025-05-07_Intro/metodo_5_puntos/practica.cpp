#include <iostream>
#include <fstream>
#include <cmath>
#include "derivatives.h"  // Debe tener la declaración de five_point_diff también

double f(double x);

int main(int argc, char **argv) {
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    double x = 1.2345;
    double exact_result = 2*x*std::cos(x*x);

    std::ofstream file("derivatives.txt");

    for(double h = 1.0e-20; h <= 1.0; h *= 10.0) {
        double forward_result = forward_diff(x, h, f);
        double central_result = central_diff(x, h, f);
        double five_point_result = five_point_diff(x, h, f); // <-- NUEVO

        double error_forward = std::abs(1.0 - forward_result / exact_result);
        double error_central = std::abs(1.0 - central_result / exact_result);
        double error_five_point = std::abs(1.0 - five_point_result / exact_result); // <-- NUEVO

        file << x << " " 
             << h << " "
             << forward_result << " "
             << central_result << " "
             << five_point_result << " "   // <-- NUEVO
             << error_forward << " "
             << error_central << " "
             << error_five_point           // <-- NUEVO
             << std::endl;
    }

    file.close();
    return 0;
}

double f(double x)
{
   return std::sin(x*x); // 2xcos(x^2) 
}
