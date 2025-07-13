
#pragma once

// ivp_solver.h
#include <iostream>
#include <valarray>
#include <functional>


// function template to work with "any" type
template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t fderiv, system_t & s, double tinit, double tend, double dt, printer_t writer)
{
    // vector to store derivs
    system_t dsdt(s.size());

    // time loop
    for(double t = tinit; t <= tend; t = t + dt) { // NOTE: Last time step not necessarily tf
        // compute derivs
        fderiv(s, dsdt, t);

        // compute new state. NOTE: Not using components, assuming valarray or similar
        s = s + dt*dsdt; // Euler

        // write new state
        writer(s, t);
      }
}

// Heun (Improved Euler) method
template <class deriv_t, class system_t, class printer_t>
void integrate_heun(deriv_t fderiv, system_t & s, double tinit, double tend, double dt, printer_t writer)
{
    // Vectores para almacenar k1 y k2
    system_t k1(s.size());
    system_t k2(s.size());
    system_t temp(s.size());

    for(double t = tinit; t <= tend; t += dt) {
        // k1 = f(t, y)
        fderiv(s, k1, t);

        // temp = y + h*k1
        temp = s + dt * k1;

        // k2 = f(t + h, y + h*k1)
        fderiv(temp, k2, t + dt);

        // y_{i+1} = y_i + h/2 * (k1 + k2)
        s = s + (dt / 2.0) * (k1 + k2);

        // escribir nuevo estado
        writer(s, t + dt);
    }
}

// Runge-Kutta de orden 4 (RK4)
template <class deriv_t, class system_t, class printer_t>
void integrate_rk4(deriv_t fderiv, system_t & s, double tinit, double tend, double dt, printer_t writer)
{
    // Vectores para almacenar k1, k2, k3, k4 y estado temporal
    system_t k1(s.size());
    system_t k2(s.size());
    system_t k3(s.size());
    system_t k4(s.size());
    system_t temp(s.size());

    for(double t = tinit; t <= tend; t += dt) {
        // k1 = f(t, y)
        fderiv(s, k1, t);

        // k2 = f(t + h/2, y + h/2 * k1)
        temp = s + (dt / 2.0) * k1;
        fderiv(temp, k2, t + dt / 2.0);

        // k3 = f(t + h/2, y + h/2 * k2)
        temp = s + (dt / 2.0) * k2;
        fderiv(temp, k3, t + dt / 2.0);

        // k4 = f(t + h, y + h * k3)
        temp = s + dt * k3;
        fderiv(temp, k4, t + dt);

        // y_{i+1} = y_i + h/6 (k1 + 2k2 + 2k3 + k4)
        s = s + (dt / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);

        // escribir nuevo estado
        writer(s, t + dt);
    }
}