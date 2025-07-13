#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Complex;
typedef vector<vector<Complex>> Matrix;

// Matrix multiplication
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int n = A[0].size();
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

// Scalar multiplication
Matrix multiplyMatrixByScalar(const Matrix& M, Complex scalar) {
    Matrix result = M;
    for (auto& row : result) {
        for (auto& elem : row) {
            elem *= scalar;
        }
    }
    return result;
}

// Matrix addition
Matrix addMatrices(const Matrix& A, const Matrix& B) {
    Matrix result = A;
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
            result[i][j] += B[i][j];
        }
    }
    return result;
}

// Matrix subtraction
Matrix subtractMatrices(const Matrix& A, const Matrix& B) {
    Matrix result = A;
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
            result[i][j] -= B[i][j];
        }
    }
    return result;
}

// Pauli matrix generator
Matrix pauliMatrix(char type) {
    Matrix sigma(2, vector<Complex>(2, 0.0));
    Complex i(0, 1);

    switch (type) {
        case 'x':
            sigma[0][0] = 0; sigma[0][1] = 1;
            sigma[1][0] = 1; sigma[1][1] = 0;
            break;
        case 'y':
            sigma[0][0] = 0; sigma[0][1] = -i;
            sigma[1][0] = i; sigma[1][1] = 0;
            break;
        case 'z':
            sigma[0][0] = 1; sigma[0][1] = 0;
            sigma[1][0] = 0; sigma[1][1] = -1;
            break;
        default:
            cerr << "Invalid Pauli matrix type" << endl;
    }
    return sigma;
}

// Verify commutation and anti-commutation relations
void verifyPauliRelations(double epsilon) {
    Matrix sigma_x = pauliMatrix('x');
    Matrix sigma_y = pauliMatrix('y');
    Matrix sigma_z = pauliMatrix('z');
    Matrix identity = {{1, 0}, {0, 1}};

    // Commutation relations [σ_i, σ_j] = σ_iσ_j - σ_jσ_i = 2iε_ijk σ_k
    Matrix comm_xy = subtractMatrices(multiplyMatrices(sigma_x, sigma_y), 
                                    multiplyMatrices(sigma_y, sigma_x));
    Matrix comm_yz = subtractMatrices(multiplyMatrices(sigma_y, sigma_z), 
                                    multiplyMatrices(sigma_z, sigma_y));
    Matrix comm_zx = subtractMatrices(multiplyMatrices(sigma_z, sigma_x), 
                                    multiplyMatrices(sigma_x, sigma_z));

    Matrix expected_comm_xy = multiplyMatrixByScalar(sigma_z, Complex(0, 2));
    Matrix expected_comm_yz = multiplyMatrixByScalar(sigma_x, Complex(0, 2));
    Matrix expected_comm_zx = multiplyMatrixByScalar(sigma_y, Complex(0, 2));

    // Anti-commutation relations {σ_i, σ_j} = σ_iσ_j + σ_jσ_i = 2δ_ij I
    Matrix anticomm_xx = addMatrices(multiplyMatrices(sigma_x, sigma_x), 
                                     multiplyMatrices(sigma_x, sigma_x));
    Matrix anticomm_xy = addMatrices(multiplyMatrices(sigma_x, sigma_y), 
                                     multiplyMatrices(sigma_y, sigma_x));
    Matrix anticomm_yy = addMatrices(multiplyMatrices(sigma_y, sigma_y), 
                                     multiplyMatrices(sigma_y, sigma_y));
    Matrix anticomm_zz = addMatrices(multiplyMatrices(sigma_z, sigma_z), 
                                     multiplyMatrices(sigma_z, sigma_z));

    Matrix expected_zero = {{0, 0}, {0, 0}};
    Matrix expected_2I = multiplyMatrixByScalar(identity, 2.0);

    // Check results
    auto matricesEqual = [epsilon](const Matrix& A, const Matrix& B) {
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A[0].size(); ++j) {
                if (abs(A[i][j] - B[i][j]) > epsilon) {
                    return false;
                }
            }
        }
        return true;
    };

    cout << "Commutation relations:" << endl;
    cout << "[σ_x, σ_y] == 2iσ_z: " << boolalpha 
         << matricesEqual(comm_xy, expected_comm_xy) << endl;
    cout << "[σ_y, σ_z] == 2iσ_x: " << boolalpha 
         << matricesEqual(comm_yz, expected_comm_yz) << endl;
    cout << "[σ_z, σ_x] == 2iσ_y: " << boolalpha 
         << matricesEqual(comm_zx, expected_comm_zx) << endl;

    cout << "\nAnti-commutation relations:" << endl;
    cout << "{σ_x, σ_x} == 2I: " << boolalpha 
         << matricesEqual(anticomm_xx, expected_2I) << endl;
    cout << "{σ_x, σ_y} == 0: " << boolalpha 
         << matricesEqual(anticomm_xy, expected_zero) << endl;
    cout << "{σ_y, σ_y} == 2I: " << boolalpha 
         << matricesEqual(anticomm_yy, expected_2I) << endl;
    cout << "{σ_z, σ_z} == 2I: " << boolalpha 
         << matricesEqual(anticomm_zz, expected_2I) << endl;
}

int main() {
    verifyPauliRelations(1e-6);
    return 0;
}