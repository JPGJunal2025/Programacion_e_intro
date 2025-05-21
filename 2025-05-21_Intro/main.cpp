#include <string>
#include <iostream>
#include <vector>

int main(int argc, char**argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <size>\n";
        return 1;
    }

    int size = std::atoi(argv[1]);
    std::vector<double> x(size);

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        x[i] = i;
        sum += x[i];
    }

    double average = sum / size;
    std::cout << "Average: " << average << "\n";

    return 0;
}
