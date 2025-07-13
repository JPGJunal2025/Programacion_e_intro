#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>

void linear_regression(const std::vector<double>& x, const std::vector<double>& y,
                       double& m, double& b, double& delta_m, double& delta_b) {
    int N = x.size();
    if (N != y.size() || N < 2) {
        std::cerr << "Error: Datos insuficientes o inconsistentes." << std::endl;
        return;
    }

    double E_x = std::accumulate(x.begin(), x.end(), 0.0) / N;
    double E_y = std::accumulate(y.begin(), y.end(), 0.0) / N;
    double E_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0) / N;
    double E_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0) / N;
    double E_yy = std::inner_product(y.begin(), y.end(), y.begin(), 0.0) / N;

    double denominator = E_xx - E_x * E_x;
    m = (E_xy - E_x * E_y) / denominator;
    b = (E_xx * E_y - E_x * E_xy) / denominator;

    double s_squared = (N / (N - 2.0)) * (E_yy - E_y * E_y - m * m * denominator);
    delta_m = std::sqrt(s_squared / (N * denominator));
    delta_b = delta_m * std::sqrt(E_xx);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <nombre_archivo>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return 1;
    }

    std::vector<double> x_data, y_data;
    double x, y;
    while (fin >> x >> y) {
        x_data.push_back(x);
        y_data.push_back(y);
    }
    fin.close();

    double m, b, delta_m, delta_b;
    linear_regression(x_data, y_data, m, b, delta_m, delta_b);

    const double e = 1.602176634e-19;
    const double h_expected = 6.62607015e-34;
    double h_calculated = m * e;
    double phi = -b;

    // Resultados en notación científica con 10 dígitos
    std::cout << std::scientific << std::setprecision(10);
    std::cout << "--------------------------------------------------\n";
    std::cout << "Resultados del ajuste lineal:\n";
    std::cout << "  Pendiente (m): " << m << " ± " << delta_m << "\n";
    std::cout << "  Intercepto (b): " << b << " ± " << delta_b << "\n";
    std::cout << "\nConstante de Planck calculada (h): " << h_calculated << " J·s\n";
    std::cout << "Constante de Planck esperada (h): " << h_expected << " J·s\n";
    std::cout << "Diferencia relativa: " << std::abs(h_calculated - h_expected) / h_expected * 100 << "%\n";
    std::cout << "\nFuncion de trabajo (ϕ): " << phi << " V\n";
    std::cout << "--------------------------------------------------\n";

    // Guardar datos para graficar
    std::ofstream fout("ajuste_lineal.txt");
    if (fout.is_open()) {
        fout << "# x y y_ajustado\n";
        for (size_t i = 0; i < x_data.size(); ++i) {
            fout << x_data[i] << " " << y_data[i] << " " << m * x_data[i] + b << "\n";
        }
        fout.close();
    }

    return 0;
}

/* El código se compila normal, g++ regresion_lineal.cpp
Para la ejecución se debe utilizar lo siguiente, (si no se hace así, no va a *funcionar*)
Primero pegar en la terminal el siguiente argumento, y dar enter, para que descargue los datos.
wget http://www-personal.umich.edu/~mejn/cp/data/millikan.txt
Luego coloque este, ./regresion_lineal millikan.txt
Si sigue correctamente las intrucciones podrá ejecutar de manera correcta el código */