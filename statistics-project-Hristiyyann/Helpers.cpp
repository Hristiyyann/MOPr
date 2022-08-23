#include "Helpers.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>   

using namespace std;

void transpose(Matrix &xMatrix, Matrix &transposeXMatrix)
{
  int rows = xMatrix.getFilledRows();
  int columns = xMatrix.getFilledColumns();
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
    {
      transposeXMatrix.matrix[j][i] = xMatrix.matrix[i][j];
    }
  }

  transposeXMatrix.setFilledColumns(xMatrix.getFilledRows());
  transposeXMatrix.setFilledRows(xMatrix.getFilledColumns());
}

void matrixMult(Matrix &first, Matrix &second, Matrix &result)
{
  int rowsFirst = first.getFilledRows(), columnsFirst = first.getFilledColumns();
  int rowsSecond = second.getFilledRows(), columnsSecond = second.getFilledColumns();

  for(int i = 0; i < rowsFirst; i++)
  {
    for(int j = 0; j < columnsSecond; j++)
    {
      for(int k=0 ; k < columnsFirst; k++)
      {
        result.matrix[i][j] += first.matrix[i][k] * second.matrix[k][j];
      }
    }
  } 

  result.setFilledRows(first.getFilledRows());
  result.setFilledColumns(second.getFilledColumns());

  return;
}

float determinant(Matrix &matrix, float k)
{
  float s = 1, det = 0;
  Matrix b = Matrix(100, 100);
  int i, j, m, n, c;

  if (k == 1)
  {
    return (matrix.matrix[0][0]);
  }

  else
  {
    det = 0;
    for (c = 0; c < k; c++)
    {
      m = 0;
      n = 0;
      for (i = 0; i < k; i++)
      {
        for (j = 0; j < k; j++)
        {
          b.matrix[i][j] = 0;
          if (i != 0 && j != c)
          {
            b.matrix[m][n] = matrix.matrix[i][j];
            if (n < (k - 2))
            n++;

            else
            {
              n = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (matrix.matrix[0][c] * determinant(b, k - 1));
      s = -1 * s;
    }
  }

  return (det);
}

void cofactor(Matrix &matrix, Matrix &end, float f)
{
  Matrix b = Matrix(10, 10);
  Matrix fac = Matrix(10, 10);

  int p, q, m, n, i, j;
  for (q = 0; q < f; q++)
  {
    for (p = 0; p < f; p++)
    {
      m = 0;
      n = 0;

      for (i = 0; i < f; i++)
      {
        for (j = 0; j < f; j++)
        {
          if (i != q && j != p)
          {
            b.matrix[m][n] = matrix.matrix[i][j];
            if (n < (f - 2))
              n++;
            else
            {
              n = 0;
              m++;
            }
          }
        }
      }
      fac.matrix[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }

  transpose(matrix, fac, end, f);
  return ;
}

void transpose(Matrix &matrix, Matrix &fac, Matrix &inverse, float r)
{
  int i, j;
  Matrix b = Matrix(10, 10);

  inverse.setFilledRows(matrix.getFilledRows());
  inverse.setFilledColumns(matrix.getFilledColumns());

  float d;

  for (i = 0; i < r; i++)
  {
    for (j = 0; j < r; j++)
    {
      b.matrix[i][j] = fac.matrix[j][i];
    }
  }

  d = determinant(matrix, r);

  for (i = 0; i < r; i++)
  {
    for (j = 0; j < r; j++)
    {
      inverse.matrix[i][j] = b.matrix[i][j] / d;
    }
  }
  return;
}

void printEquation(Matrix& matrix)
{
  int rows = matrix.getFilledRows();
  int columns = matrix.getFilledColumns();
 
  cout << "y = " << matrix.matrix[0][0];

  for (int i = 1; i < rows; i++)
  {
    if(matrix.matrix[i][0] > 0)
    {
      cout << " +" <<setprecision(4)<<matrix.matrix[i][0]<<" * x"<<i;
      continue;
    }
    cout <<" "<<setprecision(4)<<matrix.matrix[i][0]<<" * x"<<i;
  }
  cout << endl << endl; // 2 нови реда, за да е по-четимо, когато се изпринтира
}