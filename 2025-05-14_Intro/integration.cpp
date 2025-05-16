#include <iostream>
#include <fstream>
#include <cmath>
#include <functional>

using fptr = std::function<double(double)>;
using intgptr = std::function<double(double, double, int, fptr)>;

// Declaration 
double trapezoid(double a, double b, int N, fptr fun);
double simpson(double a, double b, int N, fptr fun);
double richardson_integral(double a, double b, int N, fptr f, intgptr alg, int alpha);
double f(double x);

int main(int argc, char **argv) {
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    const double a = -5.0;
    const double b = 5.0; 
    const double exact_result = 1.56898093601156;
    
    std::ofstream file("integration.txt");
    for(double N = 2; N <= 2000000; N *= 10.0) {
        double I_trap = trapezoid(a, b, N, f);
        double I_simp = simpson(a, b, N, f);
        
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

// Implementation
double trapezoid(double a, double b, int N, fptr fun)
{
    double Deltax = (b-a)/N;
    double suma = 0.0;
    for(int k = 1; k <= N-1; k++) {
        double xk = a + k*Deltax;
        suma = suma + fun(xk);
    } 
    return Deltax*(0.5*fun(a) + suma + 0.5*fun(b));
}

double simpson(double a, double b, int N, fptr fun)
{
    double Deltax = (b - a)/N;
    double suma2k = 0.0;
    for(int k = 1; k <= N/2-1; k++ ){
        double x2k = a + 2*k*Deltax;
        suma2k = suma2k + fun(x2k); 
    }
    double suma2k1 = 0.0;
    for (int k = 1; k <= N/2; k++){
        double x2k1 = a + (2*k-1)*Deltax;
        suma2k1 = suma2k1 + fun(x2k1);
    }
    return (Deltax/3)*(fun(a)+(4*suma2k1)+(2*suma2k)+ fun(b));
}

double richardson_integral(double a, double b, int N, fptr f, intgptr alg, int alpha)
{
    double aux = std::pow(2.0, alpha);
    double val1 = alg(a, b, N, f);
    double val2 = alg(a, b, 2*N, f);
    return (aux*val2 - val1)/(aux - 1.0);
}

double f(double x)
{
   return std::sin(std::exp(x));
}