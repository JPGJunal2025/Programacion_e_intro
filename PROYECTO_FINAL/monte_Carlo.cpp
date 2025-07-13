#include <random>
#include <cmath>

double monte_carlo_sin(int N) {
    double a = 0.0, b = M_PI;  // Dominio en x
    double c = 0.0, d = 1.0;   // Dominio en y (máximo de sin(x)=1)
    double area_rect = (b - a) * (d - c);
    int puntos_dentro = 0;

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(a, b);
    std::uniform_real_distribution<> dis_y(c, d);

    for (int i = 0; i < N; ++i) {
        double x = dis_x(gen);
        double y = dis_y(gen);
        
        if (y <= std::sin(x)) {
            puntos_dentro++;
        }
    }

    return area_rect * (static_cast<double>(puntos_dentro) / N);
}