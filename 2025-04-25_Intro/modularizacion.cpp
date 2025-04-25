#include <iostream>
#include <cmath>
#include <string>
#include "prime_utils.h"
void test(void);

int main(int argc, char **argv){

    int vmin = std::stoi(argv[1]);
    int vmax = std::stoi(argv[2]);

    for(int ii = vmin; ii <= vmax-4; ++ii) {
        if (isprime(ii) == true and isprime(ii+4) == true) {
            std::cout << "(" << ii << ", " << ii+4 << ") ";
        }
    }
    std::cout << "\n";

    return 0;
}

void test(void){
    //std::cout << 1 << ": " << isprime(1) << "\n";
    std::cout << 2 << ": " << isprime(2) << "\n";
    std::cout << 15 << ": " << isprime(15) << "\n";
    std::cout << 10000000019 << ": " << isprime(10000000019) << "\n";
    std::cout << 1000000007 << ": " << isprime(1000000007) << "\n";
}