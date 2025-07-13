#include "particle.h"
#include "integrator.h"
#include "collider.h"
#include "boundary.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h> 

// Función para guardar el estado en CSV
void saveToCSV(const std::vector<Particle>& particles, int iter) {
    // Crear carpeta DISPLAY si no existe
    #if defined(_linux) || defined(APPLE_)
        mkdir("DISPLAY", 0777);
    #endif

    // Nombre del archivo: data-ITER.csv
    std::string filename = "DISPLAY/data-" + std::to_string(iter) + ".csv";
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al crear el archivo: " << filename << std::endl;
        return;
    }

    // Encabezados del CSV (personaliza según tus necesidades)
    file << "x,y,z,vx,vy,vz,radius,mass\n";

    // Escribir datos de cada partícula
    for (const auto& p : particles) {
        file << p.R[0] << "," << p.R[1] << "," << p.R[2] << ","
             << p.V[0] << "," << p.V[1] << "," << p.V[2] << ","
             << p.rad << "," << p.mass << "\n";
    }

    file.close();
}

void initial_conditions(std::vector<Particle> & particles);

int main(int argc, char **argv) {
    std::vector<Particle> bodies;
    bodies.resize(1); // only one particle for now

    // parameters
    std::map<std::string, double> p;
    p["T0"] = 0.0;
    p["TF"] = 100.8767;
    p["DT"] = 0.01;
    p["G"] = 0.0; //-9.81;

    // Force collider
    Collider collider(p);

    // Time initialization
    TimeIntegrator integrator(p["DT"]);

    // Boundary conditions
    Boundary bc(2.345, 0.0, 0.0, 0.0, 0); // RMAX, CX, CY, CZ, EN

    // initial conditions and properties
    initial_conditions(bodies);
    collider.computeForces(bodies); // force at t = 0
    integrator.startIntegration(bodies); // start integration algorithm

    // Guardar estado inicial (iteración 0)
    saveToCSV(bodies, 0);

    // Time iteration
    const int niter = int((p["TF"] - p["T0"])/p["DT"]);
    const int save_interval = 10; // Guardar cada 10 iteraciones (ajusta según DT)

    for(int ii = 1; ii < niter; ++ii) {
        collider.computeForces(bodies);
        integrator.timeStep(bodies);
        bc.apply(bodies);

        // Guardar cada cierto intervalo para no saturar el disco
        if (ii % save_interval == 0) {
            saveToCSV(bodies, ii);
        }
    }

    return 0;
}

void initial_conditions(std::vector<Particle> & particles) {
    particles[0].R[2] = 0.987;  // z is upwards, x to the right
    particles[0].V[0] = 35.9876;//12.987; // z is upwards, x to the right
    particles[0].V[2] = 0.0; //4.9876; //3.987; // z is upwards, x to the right
    particles[0].rad  = 0.103;
    particles[0].mass = 0.337;
}