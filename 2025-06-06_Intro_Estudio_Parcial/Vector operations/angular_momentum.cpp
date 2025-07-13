#include <iostream>
#include <array>
#include <cmath>

using Vec3D = std::array<double, 3>;

// Función para calcular el producto cruz
Vec3D cross_product(const Vec3D& u, const Vec3D& v) {
    return {
        u[1]*v[2] - u[2]*v[1],  // Componente x
        u[2]*v[0] - u[0]*v[2],  // Componente y
        u[0]*v[1] - u[1]*v[0]   // Componente z
    };
}

// Función para calcular el momento angular L = m * r × (ω × r)
Vec3D angular_momentum(double mass, const Vec3D& position, const Vec3D& angular_velocity) {
    // Calcular v = ω × r
    Vec3D velocity = cross_product(angular_velocity, position);
    
    // Calcular L = m * r × v
    return {
        mass * cross_product(position, velocity)[0],
        mass * cross_product(position, velocity)[1],
        mass * cross_product(position, velocity)[2]
    };
}

// Función para calcular la aceleración centrípeta a = ω × (ω × r)
Vec3D centripetal_acceleration(const Vec3D& angular_velocity, const Vec3D& position) {
    // Calcular ω × r
    Vec3D temp = cross_product(angular_velocity, position);
    
    // Calcular ω × (ω × r)
    return cross_product(angular_velocity, temp);
}

// Función para imprimir vectores
void print_vector(const std::string& name, const Vec3D& v) {
    std::cout << name << " = (" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}

int main() {
    // Datos de ejemplo
    const double m = 2.5;  // masa en kg
    Vec3D r = {0.0, 3.0, 0.0};  // posición en metros
    Vec3D ω = {0.0, 0.0, 4.0};  // velocidad angular en rad/s
    
    // Calcular momento angular
    Vec3D L = angular_momentum(m, r, ω);
    print_vector("Momento angular L", L);
    
    // Calcular aceleración centrípeta
    Vec3D a = centripetal_acceleration(ω, r);
    print_vector("Aceleración centrípeta a", a);
    
    // Verificación de resultados (para movimiento circular en plano xy)
    double expected_L = m * (r[1]*r[1] + r[0]*r[0]) * ω[2];
    double expected_a = ω[2] * ω[2] * std::sqrt(r[0]*r[0] + r[1]*r[1]);
    
    std::cout << "\nVerificación:\n";
    std::cout << "Magnitud de L (teórica): " << expected_L << "\n";
    std::cout << "Magnitud de a (teórica): " << expected_a << "\n";
    
    return 0;
}