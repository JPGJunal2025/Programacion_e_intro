#include <iostream>

void modificar (int x){
    x = 42;
}

int main(){
    int a = 7;
    modificar(a);

    std::cout << "a: " << a << std::endl;

    return 0;
}