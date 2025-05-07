#include <vector>
#include <algorithm>

// dentro de largest_prime_factor o una nueva función:
std::vector<long> prime_factors;

for (long i = 2; i <= n; ++i) {
    if (n % i == 0 && isprime(i)) {
        prime_factors.push_back(i);
        while (n % i == 0) {
            n /= i;
        }
    }
}

// luego accedes así:
if (prime_factors.size() >= 2)
    return prime_factors[prime_factors.size() - 2]; // segundo mayor
