#include <iostream>
#include <array>
#include <cmath>
#include <cassert>

// Alias para vector 3D usando std::array
using Vec3D = std::array<double, 3>;

// Función para calcular el producto cruz
Vec3D cross_product(const Vec3D& a, const Vec3D& b) {
    return {
        a[1]*b[2] - a[2]*b[1],  // Componente x
        a[2]*b[0] - a[0]*b[2],  // Componente y
        a[0]*b[1] - a[1]*b[0]   // Componente z
    };
}

// Función para calcular la magnitud de un vector
double magnitude(const Vec3D& v) {
    return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

// Función para normalizar un vector (convertirlo en unitario)
Vec3D normalize(const Vec3D& v) {
    const double mag = magnitude(v);
    assert(mag > 0 && "El vector no puede ser cero");
    return {v[0]/mag, v[1]/mag, v[2]/mag};
}

// Función principal para encontrar vector perpendicular unitario
Vec3D find_perpendicular_unit_vector(const Vec3D& a, const Vec3D& b) {
    // Calcular el producto cruz
    Vec3D cross = cross_product(a, b);
    
    // Normalizar el resultado
    return normalize(cross);
}

// Función para imprimir vectores
void print_vector(const Vec3D& v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

int main() {
    // Vectores de prueba
    Vec3D i = {1, 0, 0};
    Vec3D j = {0, 1, 0};
    Vec3D k = {0, 0, 1};
    Vec3D a = {1, 2, 3};
    Vec3D b = {4, 5, 6};
    
    // Caso 1: Vectores base i y j
    Vec3D perp1 = find_perpendicular_unit_vector(i, j);
    std::cout << "Vector perpendicular a i y j: ";
    print_vector(perp1);
    std::cout << " (debería ser k)\n";
    
    // Caso 2: Vectores generales a y b
    Vec3D perp2 = find_perpendicular_unit_vector(a, b);
    std::cout << "Vector perpendicular a a y b: ";
    print_vector(perp2);
    std::cout << "\n";
    
    // Verificar ortogonalidad
    auto dot_product = [](const Vec3D& u, const Vec3D& v) {
        return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
    };
    
    std::cout << "Producto punto con a: " << dot_product(perp2, a) << "\n";
    std::cout << "Producto punto con b: " << dot_product(perp2, b) << "\n";
    
    return 0;
}