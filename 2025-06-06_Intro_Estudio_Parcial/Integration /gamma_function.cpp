#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

// Parámetros de la distribución Gamma
const double alpha = 7.5;
const double beta = 1.0;

// Función gamma PDF
double gamma_pdf(double x) {
    if (x <= 0) return 0.0;
    return (pow(beta, alpha) / tgamma(alpha)) * pow(x, alpha-1) * exp(-beta*x);
}

// Método de Simpson para integración
double simpson_integration(double a, double b, int n) {
    if (n % 2 != 0) n++; // Asegurar que n es par
    double h = (b - a) / n;
    double sum = gamma_pdf(a) + gamma_pdf(b);
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2.0 * gamma_pdf(x) : 4.0 * gamma_pdf(x);
    }
    
    return sum * h / 3.0;
}

// Puntos y pesos para cuadratura Gaussiana (n=5)
const int gauss_points = 5;
const double gauss_xi[5] = {-0.90618, -0.538469, 0.0, 0.538469, 0.90618};
const double gauss_wi[5] = {0.236927, 0.478629, 0.568889, 0.478629, 0.236927};

// Método de Gauss-Legendre para integración
double gauss_legendre_integration(double a, double b) {
    double sum = 0.0;
    double midpoint = (a + b) / 2.0;
    double half_length = (b - a) / 2.0;
    
    for (int i = 0; i < gauss_points; i++) {
        double x = midpoint + half_length * gauss_xi[i];
        sum += gauss_wi[i] * gamma_pdf(x);
    }
    
    return sum * half_length;
}

int main() {
    const double x_min = 0.0;
    const double x_max = 20.0;
    const int steps = 200;
    
    std::ofstream outfile("gamma_cdf.dat");
    outfile << std::scientific << std::setprecision(6);
    outfile << "# x\tSimpson_CDF\tGauss_CDF\n";
    
    for (int i = 0; i <= steps; i++) {
        double x = x_min + i * (x_max - x_min) / steps;
        
        // Calcular CDF con ambos métodos
        double simpson_cdf = simpson_integration(0.0, x, 1000);
        double gauss_cdf = gauss_legendre_integration(0.0, x);
        
        outfile << x << "\t" << simpson_cdf << "\t" << gauss_cdf << "\n";
    }
    
    outfile.close();
    std::cout << "Datos calculados y guardados en gamma_cdf.dat" << std::endl;
    
    return 0;
}