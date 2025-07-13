#include <iostream>
#include <vector>
#include <string>
#include <random> 
#include <cmath>


void print_matrix(const std::vector<double> & data, int m, int n);
void matmul(const std::vector<double> & A, const std::vector<double> & B,
            std::vector<double> & C, int m, int n, int p);
bool are_inverses(const std::vector<double>& A, const std::vector<double>& B, int n, double epsilon);



int main(void)
{
  std::vector<double> A = {
    1, 2,
    3, 4
};
std::vector<double> B = {
    -2, 1,
    1.5, -0.5
}; // B es la inversa de A

if (are_inverses(A, B, 2, 1e-6)) {
    std::cout << "¡Son inversas!\n";
} else {
    std::cout << "NO son inversas.\n";
}
  return 0;
}

void print_matrix(const std::vector<double> & data, int m, int n)
{
  for (int ii = 0; ii < m; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      std::cout << data[ii*n + jj] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void matmul(const std::vector<double> & A, const std::vector<double> & B,
            std::vector<double> & C, int m, int n, int p){
              for (int ii = 0; ii < m; ++ii) {
                for (int jj = 0; jj < p; ++jj) {
                  double sum = 0.0;
                  for (int k = 0; k < n; ++k){
                    sum += A[ii*n + k] * B[k*p + jj];
                  }
                  C[ii*p + jj] = sum;
                }
              }
            }

void mat_power(const std::vector<double> & A, std::vector<double> & result, int n, int power){
  std::vector<double> temp(n*n);
  std::copy(A.begin(), A.end(), result.begin()); /** Necesito inicializar result = A antes del ciclo de multiplicaciones sucesivas. La potencia A^1 debe ser igual a 𝐴.*/

  for (int i = 1; i < power; ++i) {
    matmul(result, A, temp, n, n, n);      // temp = result * A
    std::copy(temp.begin(), temp.end(), result.begin()); // result = temp
  }
}

// Esta función verifica si una matriz A es idempotente bajo cierta precisión epsilon.
// Es decir, si A^power ≈ A, comparando cada elemento con tolerancia.
bool is_idempotent(const std::vector<double> & A, int n, int power, double epsilon){
    std::vector<double> Ap(n*n);  // Aquí almacenamos A^power
    mat_power(A, Ap, n, power);   // Calculamos A^power y lo guardamos en Ap

    // Comparamos cada elemento de A^power con A
    for (int i = 0; i < n*n; ++i) {
        if (std::abs(Ap[i] - A[i]) > epsilon) {
            return false; // Si algún elemento difiere más de epsilon, no es idempotente
        }
    }
    return true; // Todos los elementos están dentro del margen -> sí es idempotente
}

bool are_inverses(const std::vector<double>& A, const std::vector<double>& B, int n, double epsilon){
    std::vector<double> AB(n*n);
    std::vector<double> BA(n*n);

    matmul(A, B, AB, n, n, n);
    matmul(B, A, BA, n, n, n);

    // Comprobar AB ≈ I
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            if (std::abs(AB[i*n + j] - expected) > epsilon) {
                return false;
            }
        }
    }

    // Comprobar BA ≈ I
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double expected = (i == j) ? 1.0 : 0.0; /*
            Si estamos en la diagonal principal (i == j), el valor debe ser 1.0.
            Si estamos fuera de la diagonal (i != j), el valor debe ser 0.0.
            */
            if (std::abs(BA[i*n + j] - expected) > epsilon) {
                return false;
            }
        }
    }

    return true;
}




