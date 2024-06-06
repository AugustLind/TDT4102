#include "Tetromino.h"
#include <map>
#include <cassert>
#include "Color.h"
    
const std::map<TetrominoType, std::vector<std::vector<int>>> initialMatrixMap {
    {TetrominoType::J, {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 1}
    }},
    {TetrominoType::T, {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}
    }},
    {TetrominoType::I, {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}    
    }},
    {TetrominoType::Z, {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}
    }},
    {TetrominoType::L, {
        {0, 0, 0},
        {1, 1, 1},
        {1, 0, 0}
    }},
    {TetrominoType::S, {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}
    }},
    {TetrominoType::O, {
        {1, 1},
        {1, 1}
    }}
};


Tetromino::Tetromino(TDT4102::Point startingPoint, TetrominoType tetType) : 
topLeftCorner{startingPoint}
{

matrixSize = static_cast<int>(initialMatrixMap.find(tetType)->second.size());
std::vector<std::vector<int>> inMatrix = initialMatrixMap.find(tetType)->second;
blockMatrix.resize(matrixSize, std::vector<TetrominoType>(matrixSize, TetrominoType::NONE));

for (int i = 0; i < matrixSize; i++){
    for (int j = 0; j < matrixSize; j++){
        if (inMatrix.at(i).at(j) == 1){
            blockMatrix.at(i).at(j) = tetType;
        } else{
            blockMatrix.at(i).at(j) = TetrominoType::NONE;
        }
    }
}

}

Tetromino::Tetromino() : topLeftCorner{0,0}, matrixSize{0} {}

void Tetromino::rotateCounterClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }

    //Andre rotasjon, med hensyn på den midtre raden
    for(int row = 0; row < matrixSize/2; row++){
        for(int column = 0; column < matrixSize; column++){
            std::swap(blockMatrix[row][column], blockMatrix[matrixSize-row-1][column]);
            
        }
    }
}

void Tetromino::rotateClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }
     
    //Andre rotasjon, med hensyn på den midtre kolonnen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize/2; column++){
            std::swap(blockMatrix[row][column], blockMatrix[row][matrixSize-column-1]);
        }
    }
}

void Tetromino::moveDown() {
    topLeftCorner.y += blockSize;
}

void Tetromino::moveLeft(){
    topLeftCorner.x -= blockSize;
}

void Tetromino::moveRight(){
     topLeftCorner.x += blockSize;
}


bool Tetromino::blockExcist(int row, int column){  
    if (blockMatrix.at(row).at(column) == TetrominoType::NONE){
        return true;
    } 
    return false;
}


TetrominoType Tetromino::getBlock(int row, int column){
    if (!blockExcist(row,column)){
        return blockMatrix[row].at(column);
    }
    return TetrominoType::NONE;
}

int Tetromino::getMatrixSize(){
    return matrixSize;
}

TDT4102::Point Tetromino::getPosition(){
    return topLeftCorner;
}   

