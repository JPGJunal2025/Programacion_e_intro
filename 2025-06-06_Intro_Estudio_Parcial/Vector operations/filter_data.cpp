#include <iostream>
#include <valarray>
#include <cmath>

int main() {
    const int N = 1000;
    const double pi = 3.14159265358979323846;
    
    // 1. Crear valarray con N puntos entre 0 y 2π
    std::valarray<double> x(N);
    for(int i = 0; i < N; ++i) {
        x[i] = i * (2 * pi) / (N - 1);
    }
    
    // 2. Calcular seno de cada elemento
    std::valarray<double> sin_x = std::sin(x);
    
    // 3. Filtrar valores donde |sen x| ≤ 0.5
    std::valarray<bool> mask = std::abs(sin_x) <= 0.5;
    std::valarray<double> filtered = sin_x[mask];
    
    // 4. Imprimir resultados
    std::cout << "Valores de sen(x) donde |sen(x)| ≤ 0.5:\n";
    for(double val : filtered) {
        std::cout << val << '\n';
    }
    
    return 0;
}