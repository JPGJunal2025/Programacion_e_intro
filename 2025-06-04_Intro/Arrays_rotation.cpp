#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// Rotated array function for x-axis
std::vector<double> createRotationX(double theta) {
    return {
        1.0, 0.0, 0.0,
        0.0, std::cos(theta), -std::sin(theta),
        0.0, std::sin(theta), std::cos(theta)
    };
}

// Rotated array function for y-axis
std::vector<double> createRotationY(double theta) {
    return {
        std::cos(theta), 0.0, std::sin(theta),
        0.0, 1.0, 0.0,
        -std::sin(theta), 0.0, std::cos(theta)
    };
}

// Rotated array function for z-axis
std::vector<double> createRotationZ(double theta) {
    return {
        std::cos(theta), -std::sin(theta), 0.0,
        std::sin(theta), std::cos(theta), 0.0,
        0.0, 0.0, 1.0
    };
}

// Multiplication of array 3x3 and vector 3x1
std::vector<double> matrixVectorMultiply(const std::vector<double>& matrix, const std::vector<double>& vector) {
    std::vector<double> result(3, 0.0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i] += matrix[i*3 + j] * vector[j];
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Uso: " << argv[0] << " vx vy vz thetax thetay thetaz\n";
        return 1;
    }

    std::vector<double> v = {
        std::stod(argv[1]),
        std::stod(argv[2]),
        std::stod(argv[3])
    };

    double theta_x = std::stod(argv[4]);
    double theta_y = std::stod(argv[5]);
    double theta_z = std::stod(argv[6]);

    // Create rotation arrays
    std::vector<double> rot_x = createRotationX(theta_x);
    std::vector<double> rot_y = createRotationY(theta_y);
    std::vector<double> rot_z = createRotationZ(theta_z);

    // Aplication of rotations
    std::vector<double> rotated = matrixVectorMultiply(rot_x, v);
    rotated = matrixVectorMultiply(rot_y, rotated);
    rotated = matrixVectorMultiply(rot_z, rotated);

    // Print the results
    std::cout.precision(6);
    std::cout << std::scientific;
    std::cout << rotated[0] << " " << rotated[1] << " " << rotated[2] << "\n";

    return 0;
}