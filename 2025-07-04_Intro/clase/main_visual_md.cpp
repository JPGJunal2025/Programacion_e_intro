// main_md.cpp
// Compilar con:
// g++ -std=c++17 -g particle.cpp main_visual_md.cpp -lsfml-window -lsfml-graphics -lsfml-system

#include "particle.h"
#include "integrator.h"
#include "collider.h"
#include "boundary.h"
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

void initial_conditions(std::vector<Particle> & particles);

int main(int argc, char **argv) {
    const int N = 1;  // ahora 200 partículas
    std::vector<Particle> bodies(N);

    // parámetros de simulación
    std::map<std::string, double> p;
    p["T0"] = 0.0;
    p["TF"] = 50.0;
    p["DT"] = 0.002;
    p["G"]  = 0.0;
    p["K"]  = 1000.0;

    // ventana
    const int WIDTH = 800, HEIGHT = 600;
    const float METERS_TO_PIXELS = 100.0f;

    // colisionador e integrador
    Collider collider(p);
    TimeIntegrator integrator(p["DT"]);
    Boundary bc(2.345, 0.0, 0.0, 0.0, 1.0);

    // condiciones iniciales
    initial_conditions(bodies);
    collider.computeForces(bodies);
    integrator.startIntegration(bodies);

    // setup visual
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Simulación MD - 200 partículas");
    window.setFramerateLimit(120);

    // precomputar colores según radio (tamaño)
    std::vector<sf::Color> colors(N);
    double rmin = 0.05, rmax = 0.25;
    for (int i = 0; i < N; ++i) {
        double t = (bodies[i].rad - rmin) / (rmax - rmin);
        // degradado de azul (pequeñas) a rojo (grandes)
        sf::Uint8 R = static_cast<sf::Uint8>(255 * t);
        sf::Uint8 B = static_cast<sf::Uint8>(255 * (1.0 - t));
        colors[i] = sf::Color(R, 0, B);
    }

    const int niter = int((p["TF"] - p["T0"]) / p["DT"]);
    sf::CircleShape shape;
    while (window.isOpen()) {
        // evento de cierre
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // paso MD
        collider.computeForces(bodies);
        integrator.timeStep(bodies);
        bc.apply(bodies);

        // dibujar todas las partículas
        window.clear(sf::Color::Black);
        for (int i = 0; i < N; ++i) {
            float rad_px = bodies[i].rad * METERS_TO_PIXELS;
            shape.setRadius(rad_px);
            shape.setOrigin(rad_px, rad_px);
            shape.setFillColor(colors[i]);

            sf::Vector2f pos;
            pos.x = WIDTH/2.f + bodies[i].R[0] * METERS_TO_PIXELS;
            pos.y = HEIGHT/2.f - bodies[i].R[2] * METERS_TO_PIXELS;
            shape.setPosition(pos);

            window.draw(shape);
        }
        window.display();
    }

    return 0;
}

void initial_conditions(std::vector<Particle> & particles) {
    std::mt19937 rng(12345);
    std::uniform_real_distribution<double> distR(-1.0, 1.0);
    std::uniform_real_distribution<double> distV(-5.0, 5.0);
    std::uniform_real_distribution<double> distRad(0.05, 0.25);
    std::uniform_real_distribution<double> distMass(0.1, 1.0);

    for (auto &pt : particles) {
    pt.R[0] = distR(rng);  // X
    pt.R[1] = 0.0;         // Y (si es 2D, mantenlo en 0)
    pt.R[2] = distR(rng);  // Z
    pt.V[0] = distV(rng);  // Vx
    pt.V[1] = 0.0;         // Vy (si es 2D, mantenlo en 0)
    pt.V[2] = distV(rng);  // Vz
    pt.rad  = distRad(rng);
    pt.mass = distMass(rng);
}
}