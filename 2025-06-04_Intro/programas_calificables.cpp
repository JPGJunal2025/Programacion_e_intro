#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>  
#include <cmath>

std::vector<double> mult_matrix_vec
(std::vector<double>& matrix , int filas, int columnas, std::vector<double>& vec); 
std::vector<double> rotacion_vector 
(double x, double y, double z, double thetax, double thetay, double thetaz);


int main(int argc, char** argv){
    double x = std::stod(argv[1]);
    double y = std::stod(argv[2]);
    double z = std::stod(argv[3]);
    double thetax = std::stod(argv[4]);
    double thetay = std::stod(argv[5]);
    double thetaz = std::stod(argv[6]);
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);
    std::vector<double> vec_r = rotacion_vector(x, y, z, thetax, thetay, thetaz);
    auto print = [](double x){ std::cout << x << "\n";};
    std::for_each(vec_r.begin(), vec_r.end(), print);
    return 0;

}

std::vector<double> mult_matrix_vec
(std::vector<double>& matrix , int filas, int columnas, std::vector<double>& vec){
    if (columnas != vec.size()){
        std::cerr << "Operación no compatible, el número de columnas debe coincidir con el tamaño del vector. " << "\n";
        return {};
    }
    std::vector<double> result ;
    for (int ii = 0; ii < filas; ii++){
        double v_ii = 0.0;
        for (int jj = 0; jj < columnas; jj++){
            double v_jj = matrix[ii*columnas+jj]*vec[jj];
            v_ii = v_ii + v_jj;
        }
        result.push_back(v_ii);
    }
    return result;
}
std::vector<double> rotacion_vector 
(double x, double y, double z, double thetax, double thetay, double thetaz){
    std::vector<double> v {x,y,z};
    std::vector<double> matrix_rotx {
        1,0,0,
        0,std::cos(thetax),-std::sin(thetax),
        0,std::sin(thetax),std::cos(thetax)
    };
    std::vector<double> matrix_roty {
        std::cos(thetay),0,std::sin(thetay),
        0,1,0,
        -std::sin(thetay),0, std::cos(thetay)
    };
    std::vector<double> matrix_rotz {
        std::cos(thetaz), -std::sin(thetaz),0,
        std::sin(thetaz), std::cos(thetaz),0,
        0,0,1
    };
    std::vector<double> vec_rot_x = mult_matrix_vec(matrix_rotx,3,3,v);
    std::vector<double> vec_rot_y = mult_matrix_vec(matrix_roty,3,3,vec_rot_x);
    std::vector<double> vec_rot_z = mult_matrix_vec(matrix_rotz,3,3,vec_rot_y);
    
    return vec_rot_z;

}
