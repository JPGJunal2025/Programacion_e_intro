#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

// Función integrando para el dilogaritmo
double dilog_integrand(double t) {
    if (t <= 0.0 || t >= 1.0) return 0.0;
    return -log(1.0 - t) / t;
}

// Declaración adelantada de la función helper
double adaptive_simpson_helper(double a, double b, double tol, double S, 
                             double fa, double fb, double fc, int depth);

// Método de Simpson adaptativo con control de error
double adaptive_simpson(double a, double b, double tol, int max_depth = 20) {
    double h = b - a;
    double c = (a + b) / 2.0;
    
    double fa = dilog_integrand(a);
    double fb = dilog_integrand(b);
    double fc = dilog_integrand(c);
    
    double S = (h / 6.0) * (fa + 4.0 * fc + fb);
    
    return adaptive_simpson_helper(a, b, tol, S, fa, fb, fc, max_depth);
}

// Implementación de la función helper
double adaptive_simpson_helper(double a, double b, double tol, double S, 
                             double fa, double fb, double fc, int depth) {
    double c = (a + b) / 2.0;
    double h = b - a;
    
    double d = (a + c) / 2.0;
    double e = (c + b) / 2.0;
    
    double fd = dilog_integrand(d);
    double fe = dilog_integrand(e);
    
    double S1 = (h / 12.0) * (fa + 4.0 * fd + fc);
    double S2 = (h / 12.0) * (fc + 4.0 * fe + fb);
    double S_total = S1 + S2;
    
    if (depth <= 0 || fabs(S_total - S) <= 15.0 * tol) {
        return S_total + (S_total - S) / 15.0;
    }
    
    return adaptive_simpson_helper(a, c, tol/2.0, S1, fa, fc, fd, depth - 1) +
           adaptive_simpson_helper(c, b, tol/2.0, S2, fc, fb, fe, depth - 1);
}

// Función dilogaritmo principal
double dilogarithm(double x) {
    if (x <= 0.0) return 0.0;
    if (x >= 1.0) return M_PI*M_PI/6.0; // Valor conocido en x=1
    
    // Para evitar problemas numéricos cerca de x=1
    if (x > 0.9) {
        return M_PI*M_PI/6.0 - dilogarithm(1.0 - x) - log(x)*log(1.0 - x);
    }
    return adaptive_simpson(0.0, x, 1e-8);
}

int main() {
    const int n_points = 200;
    const double x_min = 0.0;
    const double x_max = 1.0;
    
    std::ofstream outfile("dilog.dat");
    outfile << std::scientific << std::setprecision(10);
    outfile << "# x\tLi2(x)\n";
    
    for (int i = 0; i <= n_points; ++i) {
        double x = x_min + i * (x_max - x_min) / n_points;
        double li2 = dilogarithm(x);
        outfile << x << "\t" << li2 << "\n";
    }
    
    outfile.close();
    std::cout << "Datos del dilogaritmo guardados en dilog.dat" << std::endl;
    
    return 0;
}