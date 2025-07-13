#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>  
#include <cmath>


int main(int argc, char** argv) {
    std::string fname = argv[1];
    std::vector<double> xdata;
    std::vector<double> ydata;
    std::vector<double> xydata;
    double e = 1.602176634e-19;
    double x;
    double y;
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);
    std::ifstream fin(fname);
    while (fin >> x >> y) {
        xdata.push_back(x);
        ydata.push_back(y);
    }
    for (int ii = 0 ; ii < xdata.size(); ++ii){
        xydata.push_back(xdata[ii] * ydata[ii]);
    }
    auto print = [](double x){ std::cout << x << "\n";};

    double N = xdata.size();

    double E_xy = (1/N)*std::accumulate(xydata.begin(), xydata.end(), 0.0);
    double E_x = (1/N)*std::accumulate(xdata.begin(), xdata.end(), 0.0);
    double E_y = (1/N)*std::accumulate(ydata.begin(), ydata.end(), 0.0);
    
    auto fill_squares = [](double & x){ x = x*x;};
    std::for_each(xdata.begin(), xdata.end(), fill_squares);
    double E_xx = (1/N)*std::accumulate(xdata.begin(), xdata.end(), 0.0);
    std::for_each(ydata.begin(), ydata.end(), fill_squares);
    double E_yy = (1/N)*std::accumulate(ydata.begin(), ydata.end(), 0.0);


    double m = (E_xy - E_x * E_y)/(E_xx - E_x * E_x);
    double b = (E_xx * E_y - E_x * E_xy)/(E_xx - E_x * E_x);
    double s2 = (N*(E_yy - E_y * E_y - m * m *(E_xx - E_x * E_x)))/(N-2);
    double s = std::sqrt(s2);
    double deltam2 = s2/(N*(E_xx - E_x * E_x));
    double detalm = std::sqrt(deltam2);
    double deltab2 = deltam2 * E_xx;
    double deltab = std::sqrt (deltab2);
    double h = m*e;
    std::cout << m << " " << b << " " << h << " " << detalm << " " << deltab << "\n";
    return 0;
}