#include <iostream>
#include <vector>
#include <cmath>
#include <string> // Para std::stoi

/**
 * @brief Genera una matriz de Vandermonde
 * @param n Número de filas (y columnas, pues es cuadrada)
 * @return Matriz de Vandermonde donde elemento (i,j) = pow(i+1, j)
 */
std::vector<std::vector<double>> generateVandermonde(int n) {
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = std::pow(i + 1, j); // Usando i+1 para evitar 0^0
        }
    }
    return matrix;
}

/**
 * @brief Calcula la traza de una matriz cuadrada
 * @param matrix Matriz de entrada
 * @return Suma de elementos diagonales
 */
double computeTrace(const std::vector<std::vector<double>>& matrix) {
    double trace = 0.0;
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        trace += matrix[i][i];
    }
    return trace;
}

/**
 * @brief Imprime una matriz
 * @param matrix Matriz a imprimir
 */
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double elem : row) {
            std::cout << elem << "\t";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <tamaño_matriz>" << std::endl;
        return 1;
    }

    try {
        int n = std::stoi(argv[1]); // Conversión segura con stoi
        if (n <= 0) {
            std::cerr << "El tamaño debe ser un entero positivo" << std::endl;
            return 1;
        }

        auto vandermonde = generateVandermonde(n);
        double trace = computeTrace(vandermonde);

        std::cout << "Matriz de Vandermonde (" << n << "x" << n << "):" << std::endl;
        printMatrix(vandermonde);

        std::cout << "\nTraza de la matriz: " << trace << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Argumento no válido - debe ser un número entero" << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Número demasiado grande" << std::endl;
        return 1;
    }

    return 0;
}