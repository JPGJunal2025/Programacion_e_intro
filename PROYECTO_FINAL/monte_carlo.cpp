#include "randomcpp/Random.hpp"

double monte_carlo_randomcpp(int N) {
    double a = 0.0, b = M_PI;
    double c = 0.0, d = 1.0;
    double area_rect = (b - a) * (d - c);
    double sum = 0.0;

    // Usando RandomCPP para mejores distribuciones
    RandomCPP::UniformReal<> rand_x(a, b);
    RandomCPP::UniformReal<> rand_y(c, d);

    for (int i = 0; i < N; ++i) {
        double x = rand_x();
        double y = rand_y();
        
        if (y <= std::sin(x)) {
            sum += 1.0;
        }
    }

    return area_rect * (sum / N);
}