#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "Tipo\t\tTamaño (bytes)\tMínimo\t\t\t\tMáximo\n";
    cout << "---------------------------------------------------------------\n";

    cout << "bool\t\t" << sizeof(bool) << "\t\t"
         << boolalpha << "false" << "\t\t\t" << "true" << '\n';

    cout << "char\t\t" << sizeof(char) << "\t\t"
         << (int)numeric_limits<char>::min() << "\t\t\t"
         << (int)numeric_limits<char>::max() << '\n';

    cout << "short\t\t" << sizeof(short) << "\t\t"
         << numeric_limits<short>::min() << "\t\t\t"
         << numeric_limits<short>::max() << '\n';

    cout << "int\t\t" << sizeof(int) << "\t\t"
         << numeric_limits<int>::min() << "\t\t"
         << numeric_limits<int>::max() << '\n';

    cout << "long\t\t" << sizeof(long) << "\t\t"
         << numeric_limits<long>::min() << "\t"
         << numeric_limits<long>::max() << '\n';

    cout << "long long\t" << sizeof(long long) << "\t\t"
         << numeric_limits<long long>::min() << "\t"
         << numeric_limits<long long>::max() << '\n';

    cout << "float\t\t" << sizeof(float) << "\t\t"
         << numeric_limits<float>::lowest() << "\t"
         << numeric_limits<float>::max() << '\n';

    cout << "double\t\t" << sizeof(double) << "\t\t"
         << numeric_limits<double>::lowest() << "\t"
         << numeric_limits<double>::max() << '\n';

    cout << "long double\t" << sizeof(long double) << "\t\t"
         << numeric_limits<long double>::lowest() << "\t"
         << numeric_limits<long double>::max() << '\n';

    return 0;
}
