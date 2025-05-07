#include <iostream>
#include <iomanip>

// Number of iterations for the approximation
const int NUM_ITERATIONS = 10;

// Babylonian method to estimate square root
double estimateSqrt(double S) {
    double x = 1.0;
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        x = (x + S / x) / 2.0;
    }
    return x;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number>\n";
        return 1;
    }

    double S = std::stod(argv[1]);
    double result = estimateSqrt(S);

    std::cout << S << " "; // User input printed normally
    std::cout << std::scientific << std::setprecision(15) << result << std::endl;

    return 0;
}
