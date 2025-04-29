#include <iostream>
#include <string>

int main(int argc, char **argv){
    long n = std::stol(argv[1]);
    long Max_Prime_value = 0;
    long ii = 2;

    while (n > 1){
        if (n % ii == 0){
            Max_Prime_value = ii;
            n /= ii;
        } else {
            ++ii;
        }
    }
    
    std::cout << Max_Prime_value << "\n";
    return 0;
}