#include <iostream>
#include <cmath>
#include <string>

//declaration

bool verifyPrime(long n);

int main(int argc, char **argv){
    int n = std::stoi(argv[1]);
    long sumPrimes = 0;

    for (int ii = 2; ii <= n; ++ii){
        if(verifyPrime(ii)==true){
            sumPrimes += ii;
        }
    }
    std::cout << sumPrimes << "\n";
    return 0;
}

//implementation

bool verifyPrime(long n){
    if (n <= 1){
        std::cout <<"Out of range number" << "\n";
        return false;
    }
    bool flag = true;
    if (n == 2){
        return true;
    }
    for (long ii = 2; ii <= std::sqrt(n) + 1; ii++){
        if (n % ii == 0){
            flag = false;
            break;
        }
    }

    return flag;
}