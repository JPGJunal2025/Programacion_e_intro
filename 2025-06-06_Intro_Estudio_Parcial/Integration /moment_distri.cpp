#include <iostream>
#include <cmath>
#include <iomanip>

const double alpha = 2.0;  // Shape parameter
const double beta = 1.0;   // Rate parameter

// Gamma PDF without moment component
double gamma_pdf_base(double x) {
    if (x <= 0) return 0.0;
    return (pow(beta, alpha) / tgamma(alpha)) * pow(x, alpha-1) * exp(-beta*x);
}

// Gauss-Legendre quadrature (20 points)
const int n_points = 20;
const double gauss_x[n_points] = {
    -0.993128599, -0.963971927, -0.912234428, -0.839116972, -0.746331906,
    -0.636053681, -0.510867002, -0.373706089, -0.227785851, -0.076526521,
     0.076526521,  0.227785851,  0.373706089,  0.510867002,  0.636053681,
     0.746331906,  0.839116972,  0.912234428,  0.963971927,  0.993128599
};
const double gauss_w[n_points] = {
    0.017614007, 0.040601430, 0.062672048, 0.083276742, 0.101930120,
    0.118194532, 0.131688638, 0.142096109, 0.149172986, 0.152753387,
    0.152753387, 0.149172986, 0.142096109, 0.131688638, 0.118194532,
    0.101930120, 0.083276742, 0.062672048, 0.040601430, 0.017614007
};

double calculate_moment(int k) {
    auto integrand = [k](double t) {
        double x = t / (1 - t);
        double jacobian = 1.0 / ((1 - t) * (1 - t));
        return pow(x, k) * gamma_pdf_base(x) * jacobian;
    };
    
    double integral = 0.0;
    for (int i = 0; i < n_points; ++i) {
        double t = 0.5 * (gauss_x[i] + 1.0); // Map to [0,1]
        integral += gauss_w[i] * integrand(t);
    }
    return 0.5 * integral;
}

int main() {
    std::cout << std::scientific << std::setprecision(6);
    std::cout << "Gamma Moments (α=" << alpha << ", β=" << beta << ")\n";
    std::cout << "k\tCalculated\tTheoretical\n";
    
    for (int k = 1; k <= 10; ++k) {
        double calculated = calculate_moment(k);
        double theoretical = tgamma(alpha + k) / (pow(beta, k) * tgamma(alpha));
        
        std::cout << k << "\t" << calculated << "\t" << theoretical << "\n";
    }
    
    return 0;
}