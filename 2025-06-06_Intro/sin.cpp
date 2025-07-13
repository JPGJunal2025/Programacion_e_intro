#include <string>
#include <iostream>
#include <valarray>
#include <iomanip>
#include <numeric>


void print(std::string msg, std::valarray<double>& v)
{
    std::cout << msg << " ";
    for (double n: v) { std::cout << std::setw(3) << n; }
    std::cout << '\n';
}

int main() {
    const double N = 1000.0;
    const double pi = 3.141592653589793;

    std::valarray<double> indices(N);
    std::iota(std::begin(indices), std::end(indices), 0);

    std::valarray<double> x = (2.0 * pi * indices) / N;
    std::valarray<double> y = std::abs(std::sin(x));

    std::valarray<bool> mask = y <= 0.5;
    std::valarray<double> result = x[mask];
    print("values", result);

    return 0;
}