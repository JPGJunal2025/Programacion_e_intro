#include <iostream>
#include <string>

bool isValidNumber(const std::string& input) {
    if (input.empty() || input[0] == '-') {
        std::cout << "Negative number. Ignoring\n";
        return false;
    }
    if (input.length() > 4) {
        std::cout << "Number has more than 4 digits. Ignoring\n";
        return false;
    }
    return true;
}

void printDigits(const std::string& input) {
    std::string number = input;
    while (number.length() < 4)
        number = "0" + number;

    for (size_t i = 0; i < number.length(); ++i) {
        std::cout << number[i];
        if (i < number.length() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number>\n";
        return 1;
    }

    std::string input = argv[1];
    if (isValidNumber(input))
        printDigits(input);

    return 0;
}
