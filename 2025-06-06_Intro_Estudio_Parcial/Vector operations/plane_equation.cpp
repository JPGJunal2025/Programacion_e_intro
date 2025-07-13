#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>

using Vec3D = std::valarray<double>;

// Función para calcular la ecuación del plano
std::vector<double> plane_equation(const Vec3D& p1, const Vec3D& p2, const Vec3D& p3) {
    // Calcular dos vectores en el plano
    Vec3D v1 = p2 - p1;
    Vec3D v2 = p3 - p1;
    
    // Calcular el vector normal (producto cruz)
    Vec3D normal = {
        v1[1]*v2[2] - v1[2]*v2[1],
        v1[2]*v2[0] - v1[0]*v2[2],
        v1[0]*v2[1] - v1[1]*v2[0]
    };
    
    // Normalizar el vector normal (opcional para coeficientes más limpios)
    double norm = std::sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    normal /= norm;
    
    // Calcular el término d
    double d = -(normal[0]*p1[0] + normal[1]*p1[1] + normal[2]*p1[2]);
    
    // Devolver los coeficientes [a, b, c, d]
    return {normal[0], normal[1], normal[2], d};
}

int main() {
    // Puntos de ejemplo
    Vec3D p1 = {1.0, 2.0, 3.0};
    Vec3D p2 = {4.0, 6.0, 9.0};
    Vec3D p3 = {12.0, 11.0, 9.0};
    
    // Calcular la ecuación del plano
    std::vector<double> equation = plane_equation(p1, p2, p3);
    
    // Mostrar resultados
    std::cout << "Ecuación del plano: ";
    std::cout << equation[0] << "x + " 
              << equation[1] << "y + "
              << equation[2] << "z + "
              << equation[3] << " = 0\n";
    
    // Verificación: los puntos deben satisfacer la ecuación
    auto check_point = [&](const Vec3D& p) {
        double result = equation[0]*p[0] + equation[1]*p[1] + equation[2]*p[2] + equation[3];
        std::cout << "Punto (" << p[0] << ", " << p[1] << ", " << p[2] 
                  << ") verifica: " << std::abs(result) << " (debe ser ≈0)\n";
    };
    
    check_point(p1);
    check_point(p2);
    check_point(p3);
    
    return 0;
}