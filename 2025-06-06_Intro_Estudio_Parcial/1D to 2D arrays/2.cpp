#include <iostream>
#include <vector>
#include <string>
#include <random> 

void fill_matrix(std::vector<double> & data, int m, int n);
void print_matrix(const std::vector<double> & data, int m, int n);
void fill_matrix_random(std::vector<double> & M, const int nrows, const int ncols, const int seed);
double trace_matrix(const std::vector<double> & M, int n);
void fill_matrix_hilbert(std::vector<double> & M, int n);


int main(int argc, char **argv)
{
  const int M = std::stoi(argv[1]);
  const int N = std::stoi(argv[2]);

  if (M != N) {
  std::cerr << "Error: el trazo solo está definido para matrices cuadradas.\n";
  return 1;
}

  std::vector<double> array2d(M*N, 0.0);
  fill_matrix(array2d, M, N); // Llena con valores secuenciales
  std::cout << "Matriz con índices:\n";
  print_matrix(array2d, M, N);

  std::vector<double> array2d_random(M*N, 0.0);
  fill_matrix_random(array2d_random, M, N, 123); // usa semilla fija
  std::cout << "Matriz aleatoria:\n";
  print_matrix(array2d_random, M, N);
  
  double trace = trace_matrix(array2d_random, M); 
  std:: cout << "Trazo de una Matriz: " << trace << "\n";

  std::vector<double> array2d_Hilbert(M*N, 0.0);
  fill_matrix_hilbert(array2d_Hilbert, M);
  std::cout << "Matriz de Hilbert:\n";
  print_matrix(array2d_Hilbert, M, N);
  
  double hilbert_trace = trace_matrix(array2d_Hilbert, M);
  std::cout << "Trazo de la matriz de Hilbert: " << hilbert_trace << "\n";


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

double trace_matrix(const std::vector<double> & M, int n){
  
  double trace = 0.0;
  for (int ii = 0; ii < n ; ii++ ){
    trace += M[ii*(n + 1)]; 
  }
  return trace; 
}

void fill_matrix_hilbert(std::vector<double> & M, int n){
  for (int ii = 0; ii < n; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      M[ii*n + jj] = 1.0 / (ii+jj+1); // A_(i, j) = i*n + j = id
    }
  }

}
