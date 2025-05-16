#include <iostream>
#include <fstream>
#include "integral.h"

double f(double x);

int main(int argc, char **argv) {
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    const double a = -5.0;
    const double b = 5.0; 
    const double exact_result = 1.56898093601156;
    

    // open file for writing
    std::ofstream file("integration.txt");
    for(double N = 2; N <= 2000000; N *= 10.0) {

        double I_trap = trapezoid(-5.0, 5.0 , N ,f);
        double I_simp = simpson(-5.0, 5.0 ,N ,f);

        
        double trapecio_richardson = richardson_integral(a, b, N, f, trapezoid, 2);
        double simpson_richardson = richardson_integral(a, b, N, f, simpson, 4);
        double error_trap = std::abs(1.0 - I_trap/exact_result);
        double error_simp = std::abs(1.0 - I_simp/exact_result);
        double error_trap_r = std::abs(1.0 - trapecio_richardson/exact_result);
        double error_simp_r = std::abs(1.0 - simpson_richardson/exact_result);
        file << N << " "
                << error_trap << " "
                << error_simp << " "
                << error_trap_r << " "
                << error_simp_r << " "
                << std::endl;
    }
    file.close();
    return 0;
}

double f(double x)
{
   return std::sin(std::exp(x)); //1.56898093601156
}
