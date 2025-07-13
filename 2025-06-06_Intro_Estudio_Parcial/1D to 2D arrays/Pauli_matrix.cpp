#include <iostream>
#include <vector>
#include <complex>

using namespace std;

// Definición de tipo para simplificar
typedef complex<double> Complex;
typedef vector<vector<Complex>> Matrix;

/**
 * @brief Genera la matriz de Pauli vectorial a partir de las componentes (x, y, z).
 * @param x Componente x del vector.
 * @param y Componente y del vector.
 * @param z Componente z del vector.
 * @return Matriz de Pauli vectorial (2x2).
 */
Matrix pauliVectorMatrix(double x, double y, double z) {
    Matrix sigma(2, vector<Complex>(2));

    // Matrices de Pauli
    Complex i(0, 1); // Unidad imaginaria

    // sigma_x
    sigma[0][0] = 0;
    sigma[0][1] = 1;
    sigma[1][0] = 1;
    sigma[1][1] = 0;

    // sigma_y
    Matrix sigma_y(2, vector<Complex>(2));
    sigma_y[0][0] = 0;
    sigma_y[0][1] = -i;
    sigma_y[1][0] = i;
    sigma_y[1][1] = 0;

    // sigma_z
    Matrix sigma_z(2, vector<Complex>(2));
    sigma_z[0][0] = 1;
    sigma_z[0][1] = 0;
    sigma_z[1][0] = 0;
    sigma_z[1][1] = -1;

    // Calcula la matriz de Pauli vectorial: x*sigma_x + y*sigma_y + z*sigma_z
    Matrix result(2, vector<Complex>(2, 0.0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = x * sigma[i][j] + y * sigma_y[i][j] + z * sigma_z[i][j];
        }
    }

    return result;
}

/**
 * @brief Imprime una matriz de números complejos.
 * @param M Matriz a imprimir.
 */
void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Ejemplo de uso
int main() {
    double x = 1.0, y = 2.0, z = 3.0;
    Matrix pauliMatrix = pauliVectorMatrix(x, y, z);

    cout << "Matriz de Pauli vectorial para (x=" << x << ", y=" << y << ", z=" << z << "):" << endl;
    printMatrix(pauliMatrix);

    return 0;
}