#include <iostream>
#include <eigen3/Eigen/Dense>
#include <utility>  // para std::pair

// Función que calcula det(A) y 1/f, a partir de R1 y R2
std::pair<double, double> calcularDeterminanteYF(double R1, double R2) {
    // Definiciones internas
    double n = 1.5 + 0.25 * (R1 + R2) / 20.0; // Ejemplo: n depende de R1 y R2
    double d = std::abs(R1 - R2) / 2.0;       // Ejemplo: d también

    // Matrices de la lente gruesa
    Eigen::Matrix2d M1, M2, M3;

    M1 << 1, (n - 1) / R2,
          0, 1;

    M2 << 1, 0,
          d / n, 1;

    M3 << 1, -(n - 1) / R1,
          0, 1;

    Eigen::Matrix2d A = M1 * M2 * M3;

    double determinante = A.determinant();
    double inv_f = -A(0, 1);  // A_12 negativo

    return std::make_pair(determinante, inv_f);
}

int main() {
    double R1, R2;

    std::cout << "Ingrese R1 (radio de curvatura anterior): ";
    std::cin >> R1;
    std::cout << "Ingrese R2 (radio de curvatura posterior): ";
    std::cin >> R2;

    std::pair<double, double> resultado = calcularDeterminanteYF(R1, R2);

    std::cout << "\nResultado:\n";
    std::cout << "Determinante de A: " << resultado.first << "\n";
    std::cout << "1/f (inverso de la distancia focal): " << resultado.second << "\n";

    return 0;
}
