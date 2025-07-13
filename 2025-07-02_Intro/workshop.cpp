#include <iostream>
#include <valarray>
#include <cmath>
#include <functional>
#include <string>

// Funcion para las condiciones iniciales
void initial_conditions(std::valarray<double>& y, double omega) {
    y[0] = 1.0;  
    y[1] = 0.0;  
}

// Funcion para calcular las derivadas (oscilador armonico)
void fderiv(const std::valarray<double>& y, std::valarray<double>& dydt, double t, double omega) {
    dydt[0] = y[1];                   
    dydt[1] = -omega*omega*y[0];      
}

// Metodo de Euler
template <class deriv_t, class printer_t>
void integrate_euler(deriv_t fderiv, std::valarray<double>& s, double tinit, double tend, double dt, printer_t writer) {
    std::valarray<double> dsdt(s.size());

    for(double t = tinit; t <= tend; t += dt) {
        fderiv(s, dsdt, t);
        s = s + dt*dsdt;
        writer(s, t);
    }
}

// Metodo de Heun
template <class deriv_t, class printer_t>
void integrate_heun(deriv_t fderiv, std::valarray<double>& s, double tinit, double tend, double dt, printer_t writer) {
    std::valarray<double> k1(s.size()), k2(s.size());

    for(double t = tinit; t <= tend; t += dt) {
        fderiv(s, k1, t);
        fderiv(s + dt*k1, k2, t + dt);
        s = s + dt*(k1 + k2)/2;
        writer(s, t);
    }
}

int main(int argc, char** argv) {
    // Verificacion de argumentos de la linea de comandos
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " dt t0 tf omega\n";
        return 1;
    }

    // Leer parametros de entrada
    const double dt = std::stod(argv[1]);
    const double t0 = std::stod(argv[2]);
    const double tf = std::stod(argv[3]);
    const double omega = std::stod(argv[4]);

    // Inicializar estados
    std::valarray<double> y_euler(2), y_heun(2);
    initial_conditions(y_euler, omega);
    initial_conditions(y_heun, omega);

    // Abrir archivos de salida usando iostream
    FILE* euler_file = std::fopen("output-euler.txt", "w");
    FILE* heun_file = std::fopen("output-heun.txt", "w");

    // Funciones de escritura para cada método
    auto print_to_euler = [euler_file](const std::valarray<double>& y, double time) {
        std::fprintf(euler_file, "%f\t%f\t%f\n", time, y[0], y[1]);
    };

    auto print_to_heun = [heun_file](const std::valarray<double>& y, double time) {
        std::fprintf(heun_file, "%f\t%f\t%f\n", time, y[0], y[1]);
    };

    // Funcion derivada con omega capturado
    auto deriv = [omega](const std::valarray<double>& y, std::valarray<double>& dydt, double t) {
        fderiv(y, dydt, t, omega);
    };

    // Resolver con ambos metodos
    integrate_euler(deriv, y_euler, t0, tf, dt, print_to_euler);
    integrate_heun(deriv, y_heun, t0, tf, dt, print_to_heun);

    // Cerrar archivos
    std::fclose(euler_file);
    std::fclose(heun_file);

    return 0;
}