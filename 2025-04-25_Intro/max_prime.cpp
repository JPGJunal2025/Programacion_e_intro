#include <iostream>
#include <cmath>
#include <string>

#include "prime_utils.h"

long largest_prime_factor(long n);

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./a.out <number>\n";
        return 1;
    }

    long N = std::stol(argv[1]);

    std::cout << largest_prime_factor(N) << "\n";

    return 0;
}

long largest_prime_factor(long n) {
    long largest = -1;

    for (long i = 2; i <= n; ++i) {
        if (n % i == 0 && isprime(i)) {
            largest = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    return largest;
}
