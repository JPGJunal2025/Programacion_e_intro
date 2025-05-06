#include <iostream>
#include <fstream>
#include <cmath>
#include "derivatives.h"

double f(double x);

int main(int argc, char **argv) {
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    double x = 1.2345;
    double exact_result_1st = 2*x*std::cos(x*x); // Primera derivada
    double exact_result_2nd = 2*std::cos(x*x) - 4*x*x*std::sin(x*x); // Segunda derivada

    std::ofstream file("derivatives.txt");

    for(double h = 1.0e-6; h <= 1.0; h *= 10.0) {
        double forward_result = forward_diff(x, h, f);
        double central_result = central_diff(x, h, f);
        double second_result = second_derivative(x, h, f);

        double error_forward = std::abs(1.0 - forward_result / exact_result_1st);
        double error_central = std::abs(1.0 - central_result / exact_result_1st);
        double error_second = std::abs(1.0 - second_result / exact_result_2nd);

        file << x << " " 
             << h << " "
             << forward_result << " "
             << central_result << " "
             << second_result << " "
             << error_forward << " "
             << error_central << " "
             << error_second
             << std::endl;
    }

    file.close();
    return 0;
}

double f(double x)
{
   return std::sin(x*x);
}
