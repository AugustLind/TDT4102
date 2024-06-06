#pragma once
#include "Point.h"
#include <vector>
#include "Color.h"


enum class TetrominoType{J, L, T, S, Z, O, I, NONE};

class Tetromino {
public:
    static constexpr int blockSize {30};

    Tetromino(TDT4102::Point startingPoint, TetrominoType tetType);

    Tetromino();
    
    void rotateClockwise();
    void rotateCounterClockwise();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool blockExcist(int row, int column);
    TetrominoType getBlock(int row, int column);
    int getMatrixSize();
    TDT4102::Point getPosition();
private: 
    int matrixSize;
    TDT4102::Point topLeftCorner;
    std::vector<std::vector<TetrominoType>> blockMatrix;
};  