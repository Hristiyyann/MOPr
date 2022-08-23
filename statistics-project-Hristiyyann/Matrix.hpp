#pragma once

class Matrix
{
private:
    int rows, columns;
    int filledRows = 0, filledColumns;
public:
    double** matrix;
    Matrix(int rows, int columns);
    ~Matrix();
    int getFilledRows();
    int getFilledColumns();
    void setFilledRows(int number);
    void setFilledColumns(int number);
};