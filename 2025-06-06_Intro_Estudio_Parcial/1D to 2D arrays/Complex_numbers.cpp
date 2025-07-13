#include <iostream>
#include <vector>
#include <complex>
#include <cmath> // Para std::abs

using namespace std;

// Definición de tipo para simplificar
typedef complex<double> Complex;
typedef vector<vector<Complex>> Matrix;

/**
 * @brief Calcula la transpuesta conjugada (hermitiana) de una matriz.
 * @param M Matriz de entrada.
 * @return Matriz transpuesta conjugada.
 */
Matrix hermitianTranspose(const Matrix& M) {
    int m = M.size();
    int n = M[0].size();
    Matrix result(n, vector<Complex>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i][j] = conj(M[j][i]); // conj() obtiene el conjugado
        }
    }
    return result;
}

/**
 * @brief Multiplica dos matrices de números complejos.
 * @param A Primera matriz.
 * @param B Segunda matriz.
 * @return Resultado de la multiplicación.
 */
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int n = A[0].size(); // = B.size()
    int p = B[0].size();
    Matrix result(m, vector<Complex>(p, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * @brief Genera la matriz identidad de tamaño n x n.
 * @param n Tamaño de la matriz.
 * @return Matriz identidad.
 */
Matrix identityMatrix(int n) {
    Matrix I(n, vector<Complex>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        I[i][i] = 1.0;
    }
    return I;
}

/**
 * @brief Verifica si una matriz es hermitiana comparando |AA^† - I| < ε elemento por elemento.
 * @param M Matriz de entrada (cuadrada).
 * @param epsilon Precisión permitida.
 * @return true si es hermitiana, false en caso contrario.
 */
bool isMatrixHermitian(const Matrix& M, double epsilon) {
    int n = M.size();
    auto MH = hermitianTranspose(M); // A^†
    auto AAH = multiplyMatrices(M, MH); // AA^†
    auto I = identityMatrix(n); // I

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (abs(AAH[i][j] - I[i][j]) >= epsilon) { // abs() para complejos
                return false;
            }
        }
    }
    return true;
}

// Ejemplo de uso
int main() {
    // Matriz hermitiana de ejemplo
    Matrix hermitianMatrix = {
        {Complex(2, 0), Complex(1, 1)},
        {Complex(1, -1), Complex(3, 0)}
    };

    // Matriz no hermitiana
    Matrix nonHermitianMatrix = {
        {Complex(1, 1), Complex(2, 3)},
        {Complex(4, 5), Complex(6, 7)}
    };

    double epsilon = 1e-6;

    bool isHermitian1 = isMatrixHermitian(hermitianMatrix, epsilon);
    bool isHermitian2 = isMatrixHermitian(nonHermitianMatrix, epsilon);

    cout << "Matriz 1 es hermitiana: " << boolalpha << isHermitian1 << endl;
    cout << "Matriz 2 es hermitiana: " << boolalpha << isHermitian2 << endl;

    return 0;
}