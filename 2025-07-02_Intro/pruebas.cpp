#include <iostream>                 
#include <fstream>                              //Para los archivos
#include <valarray>                             //Para representar los estados
#include <functional>                           //para lambda
#include <cmath>                                //pow

typedef std::valarray<double> state_t;          //Alias del std::valarray. Simplificacion

// Método de Euler
//Aqui implemento el metodo de euler con derivadas (fderiv), lambda print (writer) y calculo dsdt para actualizar s
template <class deriv_t, class printer_t>
void solve_euler(deriv_t fderiv, state_t s, double tinit, double tend, double dt, printer_t writer)
{
    state_t dsdt(s.size());

    for (double t = tinit; t <= tend; t += dt) {
        fderiv(s, dsdt, t);
        writer(s, t);
        s += dt * dsdt;
    }
}

// Método de Heun
//Implemento las ecuaciones de la 1 a la 3 con derivadas (fderiv) y lambda print (writer)
template <class deriv_t, class printer_t>
void solve_heun(deriv_t fderiv, state_t s, double tinit, double tend, double dt, printer_t writer)
{
    state_t k1(s.size()), k2(s.size());

    for (double t = tinit; t <= tend; t += dt) {
        fderiv(s, k1, t);
        fderiv(s + dt * k1, k2, t + dt);
        writer(s, t);
        s += dt * (k1 + k2) / 2.0;
    }
}

int main(int argc, char** argv)
{
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " dt t0 tf omega\n";
        return 1;
    } 
    
    //Aca leo los 4 valores de la linea de comandos (los convierto a double con atof)
    double dt   = std::atof(argv[1]);               //dt
    double t0   = std::atof(argv[2]);               //t0
    double tf   = std::atof(argv[3]);               //tf
    double omega = std::atof(argv[4]);              //vel.ang

    // Condiciones iniciales: y = [x, v]
    state_t y0(2);
    y0[0] = 1.0; // x(0)
    y0[1] = 0.0; // v(0)

    // Lambda con ecuaciones del MAS: dx/dt = v, dv/dt = -omega^2 * x
    auto fderiv = [omega](const state_t& y, state_t& dydt, double /*t*/) {
        dydt.resize(2);
        dydt[0] = y[1];
        dydt[1] = -omega * omega * y[0];        //capturo omega por valor [omega]
    };

    // Escritura a archivos
    std::ofstream out_euler("output-euler.txt");    //Archivo de los resultados de Euler
    std::ofstream out_heun("output-heun.txt");      //Archivo de los resultados de Heun

    //Lambda de impresion como writer
    auto write_euler = [&out_euler](const state_t& y, double t) {
        out_euler << t << "\t" << y[0] << "\t" << y[1] << "\n";
    };

    auto write_heun = [&out_heun](const state_t& y, double t) {
        out_heun << t << "\t" << y[0] << "\t" << y[1] << "\n";
    };

    //Ejecuto ambos metodos en UNA sola corrida (como requerido, mismo y0)
    solve_euler(fderiv, y0, t0, tf, dt, write_euler);
    solve_heun(fderiv, y0, t0, tf, dt, write_heun);

    out_euler.close();
    out_heun.close();

    return 0;
}