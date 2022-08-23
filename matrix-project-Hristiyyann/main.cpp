#include <iostream>
#include <fstream>
#include <vector>
#include "matrix_functions.hpp"
using namespace std;


int main()
{
    double original_matrix[4][5];
    double matrix_copy[4][5];
    double bigger_prices[4] = {0};
    double real_prices[4] = {0.129, 1.461, 85.07, 0.132};

    setting_matrix(original_matrix);
    copy_matrix(original_matrix, matrix_copy);

    simpleGauss(original_matrix, 4, bigger_prices);

    print_output(matrix_copy, bigger_prices, real_prices);

    return 0;
}
