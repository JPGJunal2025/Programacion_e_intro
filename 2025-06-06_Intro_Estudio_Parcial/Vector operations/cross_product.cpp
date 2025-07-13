#include <array>
#include <iostream>
#include <cmath>
#include <vector>

using Vec3D = std::array<double, 3>;

Vec3D cross_product(const Vec3D& a, const Vec3D& b) {
    return {
        a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]
    };
}
// Función para imprimir vectores
void print_vector(const Vec3D& v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

// Función para calcular la magnitud de un vector
double magnitude(const Vec3D& v) {
    double sum = 0.0;
    for (double component : v) {
        sum += component * component;
    }
    return std::sqrt(sum);
}

double angle_between(const Vec3D& a, const Vec3D& b) {
    double mag_a = magnitude(a);
    double mag_b = magnitude(b);
    double mag_cross = magnitude(cross_product(a, b));
    
    // Evitar división por cero
    if (mag_a == 0 || mag_b == 0) return 0.0;
    
    return std::asin(mag_cross / (mag_a * mag_b));
}

int main() {
    // Casos de prueba
    Vec3D i = {1, 0, 0};
    Vec3D j = {0, 1, 0};
    Vec3D k = {0, 0, 1};
    Vec3D a = {1, 2, 3};
    Vec3D b = {4, 5, 6};
    // Prueba 1: i × j = k
    Vec3D result1 = cross_product(i, j);
    std::cout << "i × j = "; 
    print_vector(result1);
    std::cout << " (esperado: (0, 0, 1))\n";
    
    // Prueba 2: a × a = 0
    Vec3D result2 = cross_product(a, a);
    std::cout << "a × a = "; 
    print_vector(result2);
    std::cout << " (esperado: (0, 0, 0))\n";
    
    // Prueba 3: Ángulo entre i y j
    double angle = angle_between(i, j);
    std::cout << "Ángulo entre i y j: " << angle << " rad (" 
              << angle * 180/M_PI << "°)\n";
    std::cout << " (esperado: π/2 rad o 90°)\n";
    
    // Prueba 4: Ángulo entre a y b
    angle = angle_between(a, b);
    std::cout << "Ángulo entre a y b: " << angle << " rad (" 
              << angle * 180/M_PI << "°)\n";
    
    return 0;
}