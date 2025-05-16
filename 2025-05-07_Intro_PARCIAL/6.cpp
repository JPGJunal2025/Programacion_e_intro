#include <iostream>
#include <iomanip>
#include <cmath>

//declaration

double sqrt_heron(double x, double n);

//main
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <number>\n";
        return 1;
    }

    double x = std::stod(argv[1]);
    double n = std::stod(argv[2]);
    double r = sqrt_heron(x, n);

    std::cout << std::scientific << std::setprecision(4) << r << " " << std::fabs(1 - r/std::sqrt(x)) << std::endl;
    return 0;
}
//implementation

double sqrt_heron(double x, double n){
    double r = 1;
    for (int ii = 0; ii < n; ii++){

        r = ((r + x / r) / 2.0);

    }
    return r;
    
}
