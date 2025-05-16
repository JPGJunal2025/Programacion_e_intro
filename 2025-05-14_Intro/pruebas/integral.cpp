#include "integral.h"

//Integrales
double trapezoid(double a, double b, int N, fptr fun)
{
    double Deltax = (b-a)/N;
    double suma = 0.0;
    for(int k = 1; k <= N-1; k++) {
    //for(int k = N-1; k >= 1; k--) {
        double xk = a + k*Deltax;
        suma = suma + fun(xk);
    } 
    double result1 = Deltax*(0.5*fun(a) + suma + 0.5*fun(b));
    return result1;
}

double simpson(double a, double b, int N, fptr fun)
{
    double Deltax = (b - a)/N;
    double suma2k = 0.0;
    for(int k = 1; k <= N/2-1; k++ ){
        double x2k = a + 2*k*Deltax;
        suma2k = suma2k + fun (x2k); 
    }
    double suma2k1 = 0.0;
    for (int k = 1; k <= N/2; k++){
        double x2k1 = a + (2*k-1)*Deltax;
        suma2k1 = suma2k1 + fun(x2k1);
    }
    double result2 = (Deltax/3)*(fun(a)+(4*suma2k1)+(2*suma2k)+ fun(b));
    return result2;
}

double richardson_integral(double a, double b, int N, fptr f, intgptr alg, int alpha)
{
    double aux = std::pow(2.0, alpha);
    double val1 = alg(a, b, N, f);
    double val2 = alg(a, b, 2*N, f);
    return (aux*val2 - val1)/(aux - 1.0);
}

/*Derivadas
double forward_diff(double x, double h, fptr f) {
    return (f(x + h) - f(x)) / h;
}
double central_diff(double x, double h, fptr f) {
    return (f(x + h) - f(x - h)) / (2*h);
} */ 


