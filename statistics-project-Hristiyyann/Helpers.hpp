#pragma once
#include "Matrix.hpp"

void matrixMult(Matrix &first, Matrix &second, Matrix &result);
void transpose(Matrix &xMatrix, Matrix &transposeXMatrix);
float determinant(Matrix &matrix, float k);
void cofactor(Matrix &matrix, Matrix &end, float f);
void transpose(Matrix &matrix, Matrix &fac, Matrix &inverse, float r);
void printEquation(Matrix &matrix);