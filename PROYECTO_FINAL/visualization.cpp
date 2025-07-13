#include <matplot/matplot.h>

void visualizar_monte_carlo(int N) {
    std::vector<double> x_in, y_in, x_out, y_out;
    RandomCPP::UniformReal<> rand_x(0, M_PI);
    RandomCPP::UniformReal<> rand_y(0, 1);

    for (int i = 0; i < N; ++i) {
        double x = rand_x();
        double y = rand_y();
        
        if (y <= std::sin(x)) {
            x_in.push_back(x);
            y_in.push_back(y);
        } else {
            x_out.push_back(x);
            y_out.push_back(y);
        }
    }

    auto fig = matplot::figure(true);
    matplot::scatter(x_in, y_in)->color("green").marker_size(3);
    matplot::hold(matplot::on);
    matplot::scatter(x_out, y_out)->color("red").marker_size(3).marker_face(false);
    
    // Graficar función seno
    std::vector<double> x = matplot::linspace(0, M_PI, 100);
    std::vector<double> y;
    for (auto xi : x) y.push_back(std::sin(xi));
    matplot::plot(x, y, "b-")->line_width(2);
    
    matplot::title("Método Monte Carlo (N=" + std::to_string(N) + ")");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    fig->show();
}