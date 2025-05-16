#include "integration.h"

double trapezoid(double a, double b, int N, fptr fun)
{
    double Deltax = (b-a)/N;
    double suma = 0.0;
    for(int k = 1; k <= N-1; k++) {
    //for(int k = N-1; k >= 1; k--) {
        double xk = a + k*Deltax;
        suma = suma + fun(xk);
    } 
    double result = Deltax*(0.5*fun(a) + suma + 0.5*fun(b));
    return result;
}

double simpson(double a, double b, int N, fptr fun)
{
    // N must be even
	if (N % 2 != 0) {
		N++;
	}
	double Deltax = (b-a)/N;
	double suma1 = 0.0;
    for(int k = 1; k <= N/2; k++) {
		double xk = a + (2*k - 1)*Deltax;
		suma1 += fun(xk);
	}
	double suma2 = 0.0;
    for(int k = 1; k <= N/2 - 1; k++) {
		double xk = a + (2*k)*Deltax;
		suma2 += fun(xk);
	}
	double result = Deltax*(fun(a) + 4*suma1 + 2*suma2 + fun(b))/3.0;

	return result;
}

double richardson(double a, double b, int N, fptr f, algptr alg, int alpha)
{
    double aux = std::pow(2.0, alpha);
    double val1 = alg(a, b, N, f);
    double val2 = alg(a, b, 2*N, f);
    return (aux*val2 - val1)/(aux - 1.0);
}

double gauss(double a, double b, fptr fun)
{

    double x0 = -1.0/std::sqrt(3.0);
    double x1 = +1.0/std::sqrt(3.0);
    
    double w0 = 1.0;
    double w1 = 1.0;
    
    double midpoint = (a + b) / 2.0;
    double half_width = (b - a) / 2.0;
    
    // Evaluar la integral usando la cuadratura de Gauss
    double result = (w0 * fun(half_width * x0 + midpoint) + w1 * fun(half_width * x1 + midpoint)) * half_width;
    return result;
}
double gauss2(double a, double b, fptr fun)
{

    double x0 = 0.0;
    double x1 = -std::sqrt(3.0 / 5.0);
    double x2 = std::sqrt(3.0 / 5.0);
    
    double w0 = 8.0 / 9.0;
    double w1 = 5.0 / 9.0;
    double w2 = 5.0 / 9.0;

    double midpoint = (a + b) / 2.0;
    double half_width = (b - a) / 2.0;
    
    double result = (
        w0 * fun(half_width * x0 + midpoint) +
        w1 * fun(half_width * x1 + midpoint) +
        w2 * fun(half_width * x2 + midpoint)
    ) * half_width;

    return result;
}

//5 puntos

double gauss5(double a, double b, fptr fun) {
    const double x[] = {
        0.0,
        -0.5384693101056831,  0.5384693101056831,
        -0.9061798459386640,  0.9061798459386640
    };

    const double w[] = {
        0.5688888888888889,
        0.4786286704993665,  0.4786286704993665,
        0.2369268850561891,  0.2369268850561891
    };

    double midpoint = (a + b) / 2.0;
    double half_width = (b - a) / 2.0;

    double result = 0.0;
    for (int i = 0; i < 5; ++i) {
        result += w[i] * fun(half_width * x[i] + midpoint);
    }

    return result * half_width;
}

//7 puntos

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
