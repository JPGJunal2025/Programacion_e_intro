#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

// Declaración
void play(int min_val, int max_val);

int main() {
    // Inicializamos la semilla una sola vez
    std::srand(std::time(0));

    play(1, 100);
    play(2, 22);

    return 0;
}

// Implementación
void play(int min_val, int max_val) {
    const int MIN = min_val;
    const int MAX = max_val;

    // Número aleatorio entre MIN y MAX
    const int NUM = MIN + (std::rand() % (MAX - MIN + 1));

    int guessed_number = NUM / 2; // Solo valor inicial
    int attempts = 0; // Contador de intentos

    std::cout << "\nINICIA EL JUEGO\n";

    while (guessed_number != NUM) {
        std::cout << "Adivina un numero entre " << MIN << " y " << MAX << ":\n";
        std::cin >> guessed_number;
        std::cout << "Escribiste: " << guessed_number << "\n";

        // Contamos el intento
        attempts++;

        // Validación del rango 
        if (guessed_number < MIN || guessed_number > MAX) {
            std::cout << "El numero no esta en el rango.\n";
            continue;
        }

        if (guessed_number == NUM) {
            std::cout << "GANASTE!!!! 🎉\n";
            std::cout << "Lo lograste en " << attempts << " intento(s).\n";
        } else if (guessed_number > NUM) {
            std::cout << "Te pasaste.\n";
        } else { // es menor
            std::cout << "Te falta.\n";
        }
    }
}
