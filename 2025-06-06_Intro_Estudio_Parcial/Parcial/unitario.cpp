#include <iostream>
#include <valarray>
#include <cmath>
#include <vector>
#include <cassert>

// Función para calcular la magnitud de un vector
double magnitude_v(std::valarray<double>& v) {
    return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

double magnitude_n(std::valarray<double>& n){
    return std::sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
}

// Función para normalizar un vector (convertirlo en unitario)
std::valarray<double> normalize_v(std::valarray<double>& v) {
    double mag_v = magnitude_v(v);
    assert(mag_v > 0 && "El vector no puede ser cero");
    return {v[0]/mag_v, v[1]/mag_v, v[2]/mag_v};
}
std::valarray<double> normalize_n(std::valarray<double>& n) {
    double mag_n = magnitude_n(n);
    assert(mag_n > 0 && "El vector no puede ser cero");
    return {n[0]/mag_n, n[1]/mag_n, n[2]/mag_n};
}

//operaciones 
double result (std::valarray<double>& v,std::valarray<double>& n){
    std::valarray<double> v;
    std::valarray<double> n;
    std::valarray<double> result = v - (2.0*((v*n).sum())*n);
}
