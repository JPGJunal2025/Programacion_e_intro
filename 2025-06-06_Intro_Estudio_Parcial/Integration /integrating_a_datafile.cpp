#include <iostream>
#include <fstream>
#include <iomanip>

const int MAX_POINTS = 100; // Tamaño máximo de arreglos

int main() {
    const char* filename = "accel.txt";
    
    // Arreglos para almacenar datos
    double time[MAX_POINTS], acceleration[MAX_POINTS], velocity[MAX_POINTS];
    int numPoints = 0;
    
    // Abrir archivo y leer datos directamente en main
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }
    
    // Leer datos línea por línea
    while (file >> time[numPoints] >> acceleration[numPoints]) {
        numPoints++;
        if (numPoints >= MAX_POINTS) break; // No exceder el tamaño del arreglo
    }
    file.close();
    
    // Calcular velocidad por integración trapezoidal
    velocity[0] = 0.0; // Condición inicial (velocidad inicial = 0)
    
    for (int i = 1; i < numPoints; ++i) {
        double dt = time[i] - time[i-1];
        double avg_accel = (acceleration[i] + acceleration[i-1]) / 2.0;
        velocity[i] = velocity[i-1] + avg_accel * dt;
    }
    
    // Mostrar resultados
    std::cout << "Tiempo (s)\tAceleracion (m/s²)\tVelocidad (m/s)" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    
    for (int i = 0; i < numPoints; ++i) {
        std::cout << time[i] << "\t\t" << acceleration[i] << "\t\t\t" << velocity[i] << std::endl;
    }
    
    return 0;
}