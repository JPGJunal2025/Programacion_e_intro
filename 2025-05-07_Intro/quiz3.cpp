#include <iostream>

int main (void){
    int x= 3297;
    {int x=10000;
        std::cout << x << "\n";
        }
    std::cout << x << "\n";
}