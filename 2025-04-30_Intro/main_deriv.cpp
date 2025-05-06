#include <iostream>

#include "derivates.h"

double fun(double x) {
	return x * x*std::sin(x);
}

int main(int argc, char **argv) {
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);
	std::cout << deriv_forward(fun, 1.0, 0.01) << std::endl;
	std::cout << deriv_central(fun, 1.0, 0.01) << std::endl;
	std::cout << deriv_central([](double x){ return x*x*std::sin(x);}, 1.0, 0.01) << std::endl; // works for a lambda function
	std::cout << richardson(fun, 1.0, 0.01, deriv_central, 2) << std::endl;

	return 0;
}