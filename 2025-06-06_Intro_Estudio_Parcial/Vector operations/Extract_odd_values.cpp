#include <iostream>
#include <valarray>
#include <random>
#include <chrono>
#include <algorithm>

int main() {
    // Configurar generador de números aleatorios
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1000, 2500);
    
    const int N = 100; // Tamaño del valarray
    std::valarray<int> numbers(N);
    
    // Llenar el valarray sin bucle (usando std::generate)
    std::generate(std::begin(numbers), std::end(numbers), 
                 [&](){ return distribution(generator); });
    
    // Operaciones sin bucles
    auto even_mask = numbers % 2 == 0;
    std::valarray<int> even_numbers = numbers[even_mask];
    
    // Calcular media
    if (even_numbers.size() > 0) {
        double mean = even_numbers.sum() / static_cast<double>(even_numbers.size());
        std::cout << "Cantidad de pares: " << even_numbers.size() 
                  << "\nMedia: " << mean << "\n";
    }
    
    return 0;
}