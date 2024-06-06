#pragma once
#include <iostream>

void fillInFibonacciNumbers(int* result, int length);

void printArray(int* arr, int length);

void createFibonacci();

class Matrix{
    int rows;
    int columns;
    double **matrix;
public:
    Matrix (int nRows, int nColumns);
    explicit Matrix(int nRows);
    ~ Matrix();
    double get(int row, int col) const;
    void set(int row, int col, double value);
    int getRows() const;
    int getColumns() const;
    double* operator[](int i); 
    Matrix(const Matrix & rhs);
    Matrix& operator=(Matrix rhs);
    Matrix& operator+=(const Matrix& rhs);
    friend Matrix operator+(Matrix vhs, const Matrix& rhs);
};  

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

