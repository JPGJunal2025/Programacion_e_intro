#include <fstream>
#include <cmath>
#include <iomanip>

double potential(double x);
double dev_central(double x, double h);
double dev_central_richardson(double x, double h);
double electricfield(double x, double h);

int main(void)
{
    const double h = 0.02;
    const double x_min = 0.0;
    const double x_max = 2.5;
    const int n_points = static_cast<int>((x_max - x_min)/h) + 1;

    std::ofstream outfile("campo.txt");
    outfile << std::scientific << std::setprecision(16);

    for (int i = 0; i < n_points; ++i) {
        double x = x_min + i*h;
        double exact_derivative = -2.0*(sin(x) + x*cos(x));  // Negative of derivative of V(x)
        double numerical_field = electricfield(x, h);
        
        outfile << x << " " << exact_derivative << " " << numerical_field << "\n";
    }

    outfile.close();
    return 0;
}

double potential(double x)
{
    return 2.0*x*sin(x);
}

double dev_central(double x, double h)
{
    return (potential(x + h) - potential(x - h))/(2.0*h);
}

double dev_central_richardson(double x, double h)
{
    double D1 = dev_central(x, h);
    double D2 = dev_central(x, h/2.0);
    return (4.0*D2 - D1)/3.0;
}

double electricfield(double x, double h)
{
    return -dev_central_richardson(x, h);  // E_x = -dV/dx
}