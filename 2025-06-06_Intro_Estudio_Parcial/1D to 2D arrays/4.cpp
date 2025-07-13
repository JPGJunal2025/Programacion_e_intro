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
void matmul_transpose(const std::vector<double> & A, std::vector<double> & C, int m, int n);

int main(int argc, char **argv)
{
  const int M = std::stoi(argv[1]);
  const int N = std::stoi(argv[2]);

  std::vector<double> array2d1(M*N, 0.0);
  fill_matrix(array2d1, M, N); // Llena con valores secuenciales
  std::cout << "Matriz con índices:\n";
  print_matrix(array2d1, M, N);

  std::vector<double> array2d_random1(M*N, 0.0);
  fill_matrix_random(array2d_random1, M, N, 123); // usa semilla fija
  std::cout << "Matriz aleatoria:\n";
  print_matrix(array2d_random1, M, N);

  std::vector<double> multiplication_traspose(M*M, 0.0);
  matmul_transpose(array2d_random1,multiplication_traspose, M , N );
  std::cout << "Matriz multiplicacion transpuesta:\n";
  print_matrix(multiplication_traspose, M, M);

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

void matmul_transpose(const std::vector<double> & A,
                      std::vector<double> & C, int m, int n){
                                      for (int ii = 0; ii < m; ++ii) {
                                        for (int jj = 0; jj < m; ++jj) {
                                          double sum = 0.0;
                                          for (int k = 0; k < n; ++k){
                                            sum += A[ii*n + k] * A[jj*n + k];
                                          }
                                          C[ii*m + jj] = sum;
                                        }
                                      }
                                    }


