#include <iostream>
#include <fstream>
#include <sstream> 
#include "Matrix.hpp"
#include "Helpers.hpp"

using namespace std;

const int rows = 3000;
const int columns = 5;

void readDataFromFile(Matrix &xMatrix, Matrix &yMatrix)
{
  ifstream csvFile("lifeExpectancy.csv");

  int currentIndex = 0, currentRow = 0;
  int diphtheriaIndex = 14, lifeExpectancyIndex = 3, infantDeathsIndex = 5, alcoholIndex = 6, HIVIndex = 15; // Това са индексите на колоните, които ми трябват
  string line, temporary;

  xMatrix.setFilledColumns(5);
  yMatrix.setFilledColumns(1);
  
  if (csvFile.is_open())
  {
    getline(csvFile, line); // Това тук е, за да пропусна първия ред със заглавията на колоните

    while(csvFile >> temporary)
    {
      getline(csvFile, line);
      stringstream currentLine(line);
      currentIndex = 0;

      while(getline(currentLine,temporary,','))
      {
        xMatrix.matrix[currentRow][0] = 1;

        if(currentIndex == lifeExpectancyIndex)
        {
          yMatrix.matrix[currentRow][0] = atof(temporary.c_str());
        }
       
        else if(currentIndex == diphtheriaIndex)
        {
          xMatrix.matrix[currentRow][1] = atof(temporary.c_str());
        }
        
        else if(currentIndex == infantDeathsIndex)
        {
          xMatrix.matrix[currentRow][2] = atof(temporary.c_str());
        }

        else if(currentIndex == alcoholIndex)
        {
          xMatrix.matrix[currentRow][3] = atof(temporary.c_str());
        }

        else if(currentIndex == HIVIndex)
        {
          xMatrix.matrix[currentRow][4] = atof(temporary.c_str());
        } 
        currentIndex++;
      }

      xMatrix.setFilledRows(xMatrix.getFilledRows() + 1);
      yMatrix.setFilledRows(yMatrix.getFilledRows() + 1);   
      currentRow++;
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

  cout << "\nEquation for stage3 is: "<< endl;
  printEquation(end);

  return 0;
}