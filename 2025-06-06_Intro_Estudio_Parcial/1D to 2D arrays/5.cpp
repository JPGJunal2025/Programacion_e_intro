#include <iostream>
#include <vector>
#include <string>
#include <random> 
#include <cmath>

void fill_matrix(std::vector<double> & data, int m, int n);
void print_matrix(const std::vector<double> & data, int m, int n);
void fill_matrix_random(std::vector<double> & M, const int nrows, const int ncols, const int seed);
void matmul(const std::vector<double> & A, const std::vector<double> & B,
            std::vector<double> & C, int m, int n, int p);
void mat_power(const std::vector<double> & A, std::vector<double> & R, int n, int power);


int main(int argc, char **argv)
{

  
  const int M = std::stoi(argv[1]);
  const int N = std::stoi(argv[2]);
  const int K = std::stoi(argv[3]);
  
  if (M != N) {
    std::cerr << "Error: Solo se pueden elevar matrices cuadradas a una potencia.\n";
    return 1;
  }
  if (K < 1) {
    std::cerr << "Error: La potencia debe ser mayor o igual a 1.\n";
    return 1;
  }

  std::vector<double> array2d1(M*N, 0.0);
  fill_matrix(array2d1, M, N); // Llena con valores secuenciales
  std::cout << "Matriz con índices:\n";
  print_matrix(array2d1, M, N);

  std::vector<double> array2d_random1(M*N, 0.0);
  fill_matrix_random(array2d_random1, M, N, 123); // usa semilla fija
  std::cout << "Matriz aleatoria:\n";
  print_matrix(array2d_random1, M, N);

  std::vector<double> array2d_random1_3(M*N, 0.0);
  mat_power(array2d_random1,array2d_random1_3,M,3);
  std::cout << "Matriz a la tres:\n";
  print_matrix(array2d_random1_3, M, M);

  return 0;
}

void fill_matrix(std::vector<double> & data, int m, int n)
{
  for (int ii = 0; ii < m; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      data[ii*n + jj] = ii*n+jj; // A_(i, j) = i*n + j = id
    }
  }
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


void fill_matrix_random(std::vector<double> & M, const int nrows, const int ncols, const int seed){
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-1, 1);
    for (int ii = 0; ii < nrows; ii++){
        for (int jj = 0; jj < ncols; jj++){
            M[ii*ncols + jj] = dis(gen);
        }
    }

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

 /*¿Por qué std::copy(A.begin(), A.end(), result.begin())?

Porque necesito inicializar result = A antes del ciclo de multiplicaciones sucesivas. La potencia 𝐴^1 debe ser igual a 𝐴.

📌 ¿Por qué se usa temp?

Porque si hiciéramos matmul(result, A, result, ...), estaríamos escribiendo en result mientras lo estamos leyendo  lo que rompe la operación. Por eso se usa un buffer temporal.

📌 ¿Por qué matmul(result, A, temp, n, n, n)?

Porque estamos trabajando con matrices cuadradas de tamaño n×n, y matmul espera dimensiones m, n, p.

📌 ¿Qué pasa si power == 0?

No lo manejamos, pero se podría lanzar un error o devolver la matriz identidad si se quisiera completar el caso matemático.
 */

