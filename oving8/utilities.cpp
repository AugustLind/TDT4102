#include <iostream>
#include "utilities.h"
#include <cassert>
#include <utility>

void fillInFibonacciNumbers(int* result, int length){
    int a = 0;
    int b = 1;
    for (int x = 0; x < length; ++x) {;
        int temp = b;
        b += a;
        a = temp;
        result[x] = a;
    }
}

void printArray(int* arr, int length){
    for (int i = 0; i < length; i++){
        std::cout << arr[i] << std::endl;
    }
}

void createFibonacci() {
    int length{};
    std::cout << "Hvor mange tall skal beregnes i Fibonacci-rekken? Antall: ";
    std::cin >> length;
    int* arr = new int[length];
    fillInFibonacciNumbers(arr, length);
    printArray(arr,length);
}

Matrix::Matrix(int nRows, int nColumns) {
    assert(nRows > 0 && nColumns > 0);
    rows = nRows;
    columns = nColumns;
    matrix = new double *[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(int nRows) : Matrix(nRows, nRows) {
    assert(nRows > 0);
    for (int i = 0; i < rows; i++) {
        matrix[i][i] = 1;
    }
}

double Matrix::get(int row, int col) const{
    double value = matrix[row][col];
    return value;
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++){
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
}

void Matrix::set(int row, int col, double value){
    matrix[row][col] = value;
}

int Matrix::getRows() const{
    return rows;
}

int Matrix::getColumns() const{
    return columns;
}

double* Matrix::operator[](int i) {
    return matrix[i];
}
    
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getColumns(); ++j) {
            os << matrix.get(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix::Matrix(const Matrix & rhs) : rows(rhs.rows), columns(rhs.columns) {
    matrix = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

Matrix& Matrix::operator=(Matrix rhs) {
    std::swap(matrix, rhs.matrix);
    std::swap(rows, rhs.rows);
    std::swap(columns, rhs.columns);
    return *this;

}

Matrix& Matrix::operator+=(const Matrix& rhs) {
    assert(rows == rhs.rows && columns == rhs.columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] += rhs.matrix[i][j];
        }
    }
    return *this;
}

Matrix operator+(Matrix vhs,const Matrix& rhs){
    vhs += rhs;
    return vhs;
}





