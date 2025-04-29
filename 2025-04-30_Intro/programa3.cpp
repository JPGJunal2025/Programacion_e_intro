#include <iostream>
#include <string>

int Fibonacci_seq(int n);

int main (int argc, char **argv) {
    int sum_odd_numbers = 0;
    int n = std::stoi(argv[1]);
    int result = Fibonacci_seq(n);

    std::cout << result << "\n";
    return 0;

}

//implementation

int Fibonacci_seq (int n){
    int a = 1;
    int b = 2;
    int sum_odd_numbers = 0;

    while ( a <= n ){
        if (a % 2 != 0){
            sum_odd_numbers += a;
        }
        
        int next_term = a + b;
        a = b;
        b = next_term;
    }

    return sum_odd_numbers;
}








