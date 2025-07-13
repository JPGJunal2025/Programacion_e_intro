#include <iostream>
#include <vector>
#include <stdexcept> // For std::invalid_argument

/**
 * @brief Multiplies two matrices
 * @param A First matrix (m x n)
 * @param B Second matrix (n x p)
 * @return Resulting matrix (m x p)
 * @throws std::invalid_argument if matrices cannot be multiplied
 */
std::vector<std::vector<double>> matrixMultiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
    
    if (A.empty() || B.empty() || A[0].size() != B.size()) {
        throw std::invalid_argument("Invalid matrix dimensions for multiplication");
    }

    size_t m = A.size();
    size_t n = A[0].size();
    size_t p = B[0].size();
    std::vector<std::vector<double>> result(m, std::vector<double>(p, 0.0));

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            for (size_t k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

/**
 * @brief Creates an identity matrix of given size
 * @param n Size of the matrix (n x n)
 * @return Identity matrix
 */
std::vector<std::vector<double>> identityMatrix(size_t n) {
    std::vector<std::vector<double>> I(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        I[i][i] = 1.0;
    }
    return I;
}

/**
 * @brief Adds two matrices
 * @param A First matrix
 * @param B Second matrix
 * @return Matrix sum A + B
 * @throws std::invalid_argument if matrices have different dimensions
 */
std::vector<std::vector<double>> matrixAdd(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {
    
    if (A.size() != B.size() || A.empty() || A[0].size() != B[0].size()) {
        throw std::invalid_argument("Matrices must have same dimensions for addition");
    }

    std::vector<std::vector<double>> result = A;
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[0].size(); ++j) {
            result[i][j] += B[i][j];
        }
    }
    return result;
}

/**
 * @brief Multiplies a matrix by a scalar
 * @param matrix Input matrix
 * @param scalar Scalar value
 * @return Scaled matrix
 */
std::vector<std::vector<double>> matrixScalarMultiply(
    const std::vector<std::vector<double>>& matrix,
    double scalar) {
    
    std::vector<std::vector<double>> result = matrix;
    for (auto& row : result) {
        for (auto& elem : row) {
            elem *= scalar;
        }
    }
    return result;
}

/**
 * @brief Evaluates a polynomial on a matrix
 * @param A Input matrix (must be square)
 * @param coefficients Polynomial coefficients [a0, a1, ..., an]
 * @return Result of polynomial evaluation a0I + a1A + a2A² + ... + anAⁿ
 * @throws std::invalid_argument if matrix is not square or empty
 */
std::vector<std::vector<double>> evaluateMatrixPolynomial(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& coefficients) {
    
    if (A.empty() || A.size() != A[0].size()) {
        throw std::invalid_argument("Matrix must be square and non-empty");
    }

    size_t n = A.size();
    auto result = identityMatrix(n);
    result = matrixScalarMultiply(result, coefficients[0]); // a0 * I

    if (coefficients.size() == 1) {
        return result;
    }

    auto currentPower = A; // Starts at A^1
    result = matrixAdd(result, matrixScalarMultiply(currentPower, coefficients[1])); // + a1*A

    for (size_t i = 2; i < coefficients.size(); ++i) {
        currentPower = matrixMultiply(currentPower, A); // A^i = A^(i-1) * A
        result = matrixAdd(result, matrixScalarMultiply(currentPower, coefficients[i])); // + ai*A^i
    }

    return result;
}

/**
 * @brief Prints a matrix
 * @param matrix Matrix to print
 */
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double elem : row) {
            std::cout << elem << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    // Example usage
    std::vector<std::vector<double>> A = {
        {1, 2},
        {3, 4}
    };

    std::vector<double> coefficients = {1, 2, 1}; // Represents 1 + 2x + x²

    try {
        auto result = evaluateMatrixPolynomial(A, coefficients);
        std::cout << "Result of polynomial evaluation:\n";
        printMatrix(result);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}