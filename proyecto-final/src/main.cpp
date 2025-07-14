#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Modo de uso: ./main [montecarlo | redneural]" << std::endl;
        return 1;
    }

    std::string modo = argv[1];

    if (modo == "montecarlo") {
        std::system("./bin/montecarlo");
    } else if (modo == "redneural") {
        std::system("./bin/neuralnet");
    } else {
        std::cout << "Modo no reconocido: " << modo << std::endl;
    }

    return 0;
}
