#include "Stopwatch.h"
#include <vector>
#include <iostream>

// Utdelt kode til oppgave 3

void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue){
    for (int row = 0; row < matrix.size(); row++){
        for (int col = 0; col < matrix.size(); col++){
            bool isDiagonal = (row == col);
            if (isDiagonal){
                matrix.at(row).at(col) = newValue;
            }
        }
    }
}

double sumMatrix(std::vector<std::vector<double>> matrix){
    double sum;
    for (int col = 0; col < matrix.size(); col++){
        for (int row = 0; row < matrix.size(); row++){
            double value = matrix.at(row).at(col);
            sum += value;            
        }
    }
    return sum;
}

void optimizationTask() {
    
    constexpr int matrixSize = 10000;

    // Create a matrix with zeros
    std::vector<std::vector<double>> matrix;

    //initialiserer med å sette reserve fra før
    matrix.reserve(matrixSize);

    constexpr double value = 0.0;
    //Definerer konstant verdi
    
    for (int i = 0; i < matrixSize; i++){
        std::vector<double> column;
        column.reserve(matrixSize);
        //reserverer plass
        for (int j = 0; j < matrixSize; j++){
            column.push_back(value);
        }
        matrix.push_back(column);
    }

    // Set all elements on the diagonal to 0.41
    //constant verdi
    constexpr double valueDia = 0.41;
    setDiagonalValue(matrix, valueDia);
    
    // Sum all elements in the matrix
    //const igjen
    const double total = sumMatrix(matrix);

    //const igjen
    const double coolerNumber = total + 2;
    std::cout << "TDT" << coolerNumber << std::endl;
}