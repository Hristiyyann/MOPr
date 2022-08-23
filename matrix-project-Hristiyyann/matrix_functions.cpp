#include "matrix_functions.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

void simpleGauss(double A[][5], int n, double prices[4])
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double delimeter = -(A[j][i] / A[i][i]);
            for (int k = i; k < n + 1; ++k)
            {
                A[j][k] += delimeter * A[i][k];
            }
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        prices[i] = A[i][n] / A[i][i];
        for (int j = n - 1; i < j; --j)
        {
            prices[i] -= (prices[j] * A[i][j]) / A[i][i];
        }
    }
}

void setting_matrix(double matrix[][5])
{
    double value;
    int count_read_values = 0, i = 0, j = 0;
    vector<double> values;

    ifstream file("values.txt");

    if (file.is_open())
    {
        while (file >> value)
        {
            values.push_back(value);
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            matrix[i][j] = values.front();
            values.erase(values.begin());
        }
    }

    j = 4;
    i = 0;

    while (!values.empty())
    {
        matrix[i][j] = values.front();
        values.erase(values.begin());
        i++;
    }
}

void copy_matrix(double matrix[][5], double matrix_copy[][5])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix_copy[i][j] = matrix[i][j];
        }
    }
}

void print_output(double matrix[][5], double bigger_prices[4], double real_prices[4])
{
    int row = 0, column = 4, index = 0;
    double final_matrix[4][4];
    double total_price = 0;
    vector<double> difference_in_prices;

    for (row = 0; row < 4; row++)
    {
        total_price += matrix[row][0] * (bigger_prices[0] - real_prices[0]);
        total_price += matrix[row][1] * (bigger_prices[1] - real_prices[1]);
        total_price += matrix[row][2] * (bigger_prices[2] - real_prices[2]);
        total_price += matrix[row][3] * (bigger_prices[3] - real_prices[3]);

        difference_in_prices.push_back(total_price);
        total_price = 0;

        for (column = 0; column < 4; column++)
        {
            index = column;
            final_matrix[row][column] = matrix[row][column] - (matrix[row][column] * real_prices[index]) / bigger_prices[index];
        }
    }

    for (auto price : difference_in_prices)
    {
        cout << price << ' ';
    }

    cout << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << round(final_matrix[i][j] * 10000.0) / 10000.0 << ' ';
        }
        cout << endl;
    }
}