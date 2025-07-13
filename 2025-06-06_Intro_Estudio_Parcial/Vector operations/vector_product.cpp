#include <iostream>
#include <array>
#include <cassert>

using Vec3D = std::array<double, 3>;

// Función para calcular el producto cruz
Vec3D cross_product(const Vec3D& b, const Vec3D& c) {
    return {
        b[1]*c[2] - b[2]*c[1],  // Componente x
        b[2]*c[0] - b[0]*c[2],  // Componente y
        b[0]*c[1] - b[1]*c[0]   // Componente z
    };
}

// Función para calcular el producto punto
double dot_product(const Vec3D& a, const Vec3D& b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

// Función para calcular el producto mixto A · (B × C)
double scalar_triple_product(const Vec3D& a, const Vec3D& b, const Vec3D& c) {
    Vec3D cross = cross_product(b, c);
    return dot_product(a, cross);
}

// Función para imprimir vectores
void print_vector(const Vec3D& v) {
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

int main() {
    // Vectores de prueba
    Vec3D a = {1.0, 0.0, 0.0};
    Vec3D b = {0.0, 1.0, 0.0};
    Vec3D c = {0.0, 0.0, 1.0};
    Vec3D d = {1.0, 2.0, 3.0};
    Vec3D e = {4.0, 5.0, 6.0};
    Vec3D f = {7.0, 8.0, 9.0};
    
    // Caso 1: Vectores base (i, j, k)
    double result1 = scalar_triple_product(a, b, c);
    std::cout << "A · (B × C) = " << result1 << " (debería ser 1.0)\n";
    
    // Caso 2: Vectores coplanares (deben dar volumen cero)
    double result2 = scalar_triple_product(d, e, f);
    std::cout << "D · (E × F) = " << result2 << " (debería ser ≈0)\n";
    
    return 0;
}