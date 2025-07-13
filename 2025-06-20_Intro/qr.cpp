# include <iostream>
# include <eigen3/Eigen/Dense>
#include <chrono>

int main()
{
    int N;
    std::cout << "Enter the size N of the matrix and vector: ";
    std::cin >> N;

    // Crear matriz y vector aleatorios
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N);
    Eigen::VectorXd b = Eigen::VectorXd::Random(N);

    // Imprimir la matriz A y el vector b
    std::cout << "\nMatrix A:\n" << A << "\n";
    std::cout << "\nVector b:\n" << b << "\n";

    // Medir el tiempo de resolución
    auto start = std::chrono::high_resolution_clock::now();
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    // Imprimir resultados
    std::cout << "\nSolution x:\n" << x << "\n";
    std::cout << "Time taken to solve (seconds): " << elapsed.count() << "\n";
    std::cout << "Residual norm ||Ax - b|| = " << (A * x - b).norm() << "\n";

    return 0;
}