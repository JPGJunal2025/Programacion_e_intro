#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
//declaration

double sqrt_heron(double x, double n);

//main
int main(void) {

    double x = 3141.5926;
    double n = (1 <= n <= 20);
    double r = sqrt_heron(x, n);

    std::cout << std::scientific << std::setprecision(4) << r << " " << std::fabs(1 - r/std::sqrt(x)) << std::endl;
    return 0;

    // open file for writing
    std::ofstream file("prueba.txt");

    for(double x = 3141.5926; n = 20;) {
        double  r = sqrt_heron(x, n);
        double error_r = std::abs(1 - r/std::sqrt(x));
        file << r << " " 
                << error_r << " "
                << std::endl;
    }
    file.close();
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
