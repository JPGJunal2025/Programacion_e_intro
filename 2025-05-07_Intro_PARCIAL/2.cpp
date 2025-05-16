#include <iostream>

bool check (void){
    int p = 0;
    int q = 0;
    int r = 0;
    bool result = true;
    result = p && q || !r;
    return result;
}

int main (void){
    bool resultado = check ();
    std::cout << resultado << "\n";
}




