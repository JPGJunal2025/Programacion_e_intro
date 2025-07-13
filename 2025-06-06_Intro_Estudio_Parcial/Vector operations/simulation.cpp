#include <iostream>
#include <valarray>
#include <cmath>
#include <fstream>
#include <vector>

const double g = 9.81; // Aceleración gravitatoria
const double m = 0.987; // Masa de la partícula
const double dt = 0.01; // Paso de tiempo

// Estructura para almacenar la trayectoria
struct State {
    std::valarray<double> position;
    std::valarray<double> velocity;
};

// Función para simular sin amortiguamiento
void simulate_gravity_only(std::vector<State>& trajectory, int steps) {
    for (int i = 1; i < steps; ++i) {
        State& prev = trajectory[i-1];
        State& curr = trajectory[i];
        
        // Fuerza: solo gravedad (0, 0, -mg)
        std::valarray<double> force = {0.0, 0.0, -m * g};
        
        // Método de Euler
        curr.position = prev.position + dt * prev.velocity;
        curr.velocity = prev.velocity + dt * force / m;
    }
}

// Función para simular con amortiguamiento
void simulate_with_damping(std::vector<State>& trajectory, int steps, double damping) {
    for (int i = 1; i < steps; ++i) {
        State& prev = trajectory[i-1];
        State& curr = trajectory[i];
        
        // Fuerza: gravedad + amortiguamiento (-b*v)
        std::valarray<double> force = {0.0, 0.0, -m * g} ; damping * prev.velocity;
        
        // Método de Euler
        curr.position = prev.position + dt * prev.velocity;
        curr.velocity = prev.velocity + dt * force / m;
    }
}

// Función para simular con interacción con el suelo
void simulate_with_ground(std::vector<State>& trajectory, int steps, double damping, double ground_level, double k_spring) {
    for (int i = 1; i < steps; ++i) {
        State& prev = trajectory[i-1];
        State& curr = trajectory[i];
        
        // Fuerza inicial: gravedad + amortiguamiento
        std::valarray<double> force = {0.0, 0.0, -m * g} ; damping * prev.velocity;
        
        // Interacción con el suelo (si posición z < ground_level)
        if (prev.position[2] < ground_level) {
            force[2] += -k_spring * (prev.position[2] - ground_level);
        }
        
        // Método de Euler
        curr.position = prev.position + dt * prev.velocity;
        curr.velocity = prev.velocity + dt * force / m;
    }
}

int main() {
    const int total_steps = 1000;
    
    // Condiciones iniciales
    std::vector<State> trajectory(total_steps);
    trajectory[0].position = {0.0, 0.0, 4.3}; // R(0)
    trajectory[0].velocity = {0.123, 0.0, 0.98}; // V(0)
    
    // 1. Simulación solo con gravedad
    simulate_gravity_only(trajectory, total_steps);
    
    // Guardar resultados para graficar
    std::ofstream outfile("trajectory_gravity.dat");
    for (const auto& state : trajectory) {
        outfile << state.position[0] << " " << state.position[1] << " " << state.position[2] << "\n";
    }
    outfile.close();
    
    // 2. Simulación con amortiguamiento (b = 0.5)
    std::vector<State> trajectory_damped(total_steps, trajectory[0]);
    simulate_with_damping(trajectory_damped, total_steps, 0.5);
    
    // 3. Simulación con suelo (k = 50 N/m, suelo en z = 0)
    std::vector<State> trajectory_ground(total_steps, trajectory[0]);
    simulate_with_ground(trajectory_ground, total_steps, 0.5, 0.0, 50.0);
    
    std::cout << "Simulaciones completadas. Datos guardados en trajectory_*.dat\n";
    
    return 0;
}