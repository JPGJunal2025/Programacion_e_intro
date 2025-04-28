#include <iostream>
#include <cmath>
#include <string>

//declaration

bool verifyPrime(long n);

int main(int argc, char **argv){
    long n = std::stol(argv[1]);
    long Max_Prime_value = 0;

    for (int ii = 2; ii <= n; ++ii){
        while (n % ii == 0)
        {
        if (verifyPrime(ii)){
            Max_Prime_value = ii;
        }
            break;
        }
    }
    std::cout << Max_Prime_value << "\n";
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