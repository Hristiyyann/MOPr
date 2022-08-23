#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Helpers.hpp"

using namespace std;

const int rows = 3000;
const int columns = 3;

void readDataFromFile(Matrix &xMatrix, Matrix &yMatrix)
{
  ifstream csvFile("lifeExpectancyStage2.csv");

  int currentRow = 0;
  string lifeExpectancy, adultMortality, GDP;

  xMatrix.setFilledColumns(3);
  yMatrix.setFilledColumns(1);

  if (csvFile.is_open())
  {
    getline(csvFile, lifeExpectancy, ',');  // Добавям тези 3 реда, за да мога да пропусна първия ред с имената на колоните от файла.
    getline(csvFile, adultMortality, ',');
    getline(csvFile, GDP, '\n'); // Така в долния цикъл започвам да чета директно стойностите

    while (getline(csvFile, lifeExpectancy, ',') && getline(csvFile, adultMortality, ','))
    {
      getline(csvFile, GDP, '\n');
    
      xMatrix.matrix[currentRow][0] = 1;
      xMatrix.matrix[currentRow][1] = atof(adultMortality.c_str());
      xMatrix.matrix[currentRow][2] = atof(GDP.c_str());
      yMatrix.matrix[currentRow][0] = atof(lifeExpectancy.c_str());
    
      currentRow++;
      xMatrix.setFilledRows(xMatrix.getFilledRows() + 1);
      yMatrix.setFilledRows(yMatrix.getFilledRows() + 1);
    }
  }
}

int main()
{
  Matrix xMatrix = Matrix(rows, columns);
  Matrix transposeXMatrix = Matrix(columns, rows);
  Matrix yMatrix = Matrix(rows, 1);
  Matrix productXMWithTXM = Matrix(columns, columns);
  Matrix productTXMWithY = Matrix(columns, 1);
  Matrix inverted = Matrix(10,10);
  Matrix end = Matrix(10, 10);

  readDataFromFile(xMatrix, yMatrix);
  transpose(xMatrix, transposeXMatrix);
  matrixMult(transposeXMatrix, xMatrix, productXMWithTXM);
  matrixMult(transposeXMatrix, yMatrix, productTXMWithY);

  determinant(productXMWithTXM, columns);
  cofactor(productXMWithTXM, inverted, columns);

  matrixMult(inverted, productTXMWithY, end);

  cout << "\nEquation for stage2 is: "<< endl;
  printEquation(end);

  return 0;
}