#include <iostream>

int main(void){
    int i;
    for (i=0; i < 5; i++){
        if (i == 2)
            break;
    }
    std::cout << i << "\n";
}