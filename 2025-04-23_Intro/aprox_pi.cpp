#include <iostream>
#include <cmath>
#include <iomanip>

double pi_aprox(int n) {
    double sum = 0.0;
    for (int k = 0; k <= n; k++) {
        double term = 1.0 / std::pow(16, k);
        term *= (4.0/(8*k + 1) - 2.0/(8*k + 4) - 1.0/(8*k + 5) - 1.0/(8*k + 6));
        sum += term;
    }
    return sum;
}

int main() {
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);

    std::cout << "---------------------------------------------------------------\n";
    std::cout << "|"
              << std::setw(15)  << "Terminos (n)"       << " | "
              << std::setw(23) << "Aproximacion"   << " | "
              << std::setw(23) << "Error Relativo" << " |\n";
    std::cout << "---------------------------------------------------------------\n";

    for (int n = 1; n <= 20; n++) {
        double aprox = pi_aprox(n);
        double error_relativo = std::abs(1 - aprox/M_PI);

        std::cout << "|"
                  << std::setw(15)  << n << " | "
                  << std::setw(23) << aprox << " | "
                  << std::setw(23) << error_relativo << " |\n";
    }

    std::cout << "---------------------------------------------------------------\n";
    return 0;
}
