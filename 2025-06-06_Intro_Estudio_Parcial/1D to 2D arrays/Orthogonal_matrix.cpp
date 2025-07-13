#include <iostream>
#include <vector>
#include <cmath>

std::vector<std::vector<double>> transposeMatrix(
    const std::vector<std::vector<double>>& M) {

    int m = M.size();
    int n = M[0].size();
    std::vector<std::vector<double>> result(n, std::vector<double>(m, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i][j] = M[j][i];
        }
    }
    return result;
}

std::vector<std::vector<double>> multiplyMatrices(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {

    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    std::vector<std::vector<double>> result(m, std::vector<double>(p, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

std::vector<std::vector<double>> identityMatrix(int n) {
    std::vector<std::vector<double>> I(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        I[i][i] = 1.0;
    }
    return I;
}

bool isMatrixOrthogonal(
    const std::vector<std::vector<double>>& M,
    double epsilon) {

    int n = M.size();
    auto MT = transposeMatrix(M);
    auto AAT = multiplyMatrices(M, MT);
    auto I = identityMatrix(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (std::abs(AAT[i][j] - I[i][j]) >= epsilon) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<double>> orthogonalMatrix = {
        {0, -1},
        {1,  0}
    };

    std::vector<std::vector<double>> nonOrthogonalMatrix = {
        {1, 2},
        {3, 4}
    };

    double epsilon = 1e-6;

    bool isOrthogonal1 = isMatrixOrthogonal(orthogonalMatrix, epsilon);
    bool isOrthogonal2 = isMatrixOrthogonal(nonOrthogonalMatrix, epsilon);

    std::cout << "Matriz 1 es ortogonal: " << std::boolalpha << isOrthogonal1 << std::endl;
    std::cout << "Matriz 2 es ortogonal: " << std::boolalpha << isOrthogonal2 << std::endl;

    return 0;
}