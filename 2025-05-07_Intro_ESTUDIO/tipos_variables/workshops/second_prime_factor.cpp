#include <iostream>
#include <string>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <número>" << std::endl;
        return 1;
    }

    long n = std::stol(argv[1]);
    long largest_prime = 0;
    long second_largest_prime = 0;
    long ii = 2;

    while (ii * ii <= n) {  // Optimización: solo verificar hasta sqrt(n)
        if (n % ii == 0) {
            if (ii > largest_prime) {
                second_largest_prime = largest_prime;
                largest_prime = ii;
            } else if (ii > second_largest_prime) {
                second_largest_prime = ii;
            }
            n /= ii;
        } else {
            ++ii;
        }
    }

    // Al salir del bucle, si n > 1, entonces n es un número primo
    if (n > 1) {
        if (n > largest_prime) {
            second_largest_prime = largest_prime;
            largest_prime = n;
        } else if (n > second_largest_prime) {
            second_largest_prime = n;
        }
    }

    // Si no hay segundo mayor (ej: números primos), se imprime el mayor
    std::cout << (second_largest_prime != 0 ? second_largest_prime : largest_prime) << "\n";
    return 0;
}