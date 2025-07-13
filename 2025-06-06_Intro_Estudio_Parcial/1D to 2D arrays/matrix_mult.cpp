#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

// Function declaration for matrix multiplication
void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3);

int main(int argc, char **argv) {
  // Validate command line arguments
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <matrix_size> <seed>\n";
    return 1;
  }

  // read parameters
  const int N = std::atoi(argv[1]);
  const int SEED = std::atoi(argv[2]);

  // data structs
  std::vector<double> A(N*N, 0.0), B(N*N, 0.0), C(N*N, 0.0);

  // fill matrices A and B with random numbers between 0 and 1
  std::mt19937 gen(SEED); // Mersenne Twister random number generator
  std::uniform_real_distribution<> dist(0.,1.); // Uniform distribution between 0 and 1
  
  // Fill matrices using lambda functions
  std::generate(A.begin(), A.end(), [&gen, &dist](){ return dist(gen); });
  std::generate(B.begin(), B.end(), [&gen, &dist](){ return dist(gen); });

  // multiply the matrices A and B and save the result into C. Measure time
  auto start = std::chrono::high_resolution_clock::now();
  multiply(A, B, C);
  auto stop = std::chrono::high_resolution_clock::now();

  // use the matrix to avoid the compiler removing it
  std::cout << "Value\n";
  std::cout << "1\n";
  std::cout << C[N/2] << std::endl;
  std::cout << "2\n";

  // print time
  auto elapsed = std::chrono::duration<double>(stop - start);
  std::cout << elapsed.count() << "\n";

  return 0;
}

// Matrix multiplication implementation
void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3)
{
  const int N = std::sqrt(m1.size()); // assumes square matrices
  
  // Initialize result matrix to zero
  std::fill(m3.begin(), m3.end(), 0.0);
  
  // Perform matrix multiplication
  for (int i = 0; i < N; ++i) {
    for (int k = 0; k < N; ++k) {
      for (int j = 0; j < N; ++j) {
        m3[i*N + j] += m1[i*N + k] * m2[k*N + j];
      }
    }
  }
}