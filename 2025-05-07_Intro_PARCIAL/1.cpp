#include <iostream>

int foo(int& x){
    x = x + 1;
    return x * 2;
}
int main (){
    int a = 5;
    int b = foo(a);
    std::cout << a << " " << b << std::endl;
    return 0;
}