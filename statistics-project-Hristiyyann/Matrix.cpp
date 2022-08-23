#include "Matrix.hpp"
#include <iostream>
using namespace std;


int Matrix::getFilledColumns()
{
    return filledColumns;
}

int Matrix::getFilledRows()
{
    return filledRows;
}

void Matrix::setFilledRows(int number)
{
    this->filledRows = number;
}

void Matrix::setFilledColumns(int number)
{
    this->filledColumns = number;
}

Matrix::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;

    matrix = new double*[rows];

    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new double[columns];
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}