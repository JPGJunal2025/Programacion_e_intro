#include <iostream>
#include <cmath>
using namespace std;

// Función auxiliar para verificar si un número es primo
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int root = sqrt(n);
    for (int i = 3; i <= root; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Función que imprime la n-ésima pareja de primos gemelos
pair<int, int> nth_twin_primes(int n) {
    int count = 0;
    int i = 3;
    while (true) {
        if (isPrime(i) && isPrime(i + 2)) {
            count++;
            if (count == n) {
                cout << "(" << i << ", " << i + 2 << ")" << endl;
                return {i, i + 2};
            }
        }
        i += 2; // Solo probar impares
    }
}
