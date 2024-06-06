#include "TetrisWindow.h"
#include <iostream>
#include <random>
#include <map>
#include "Color.h"
#include <iostream>
#include <fstream>
#include <functional> 

std::map<TetrominoType, TDT4102::Color> tetrominoColorMap{
    {TetrominoType::NONE, TDT4102::Color::gray},
    {TetrominoType::J, TDT4102::Color::dark_blue},
    {TetrominoType::L, TDT4102::Color::orange},
    {TetrominoType::T, TDT4102::Color::purple},
    {TetrominoType::S, TDT4102::Color::light_green},
    {TetrominoType::Z, TDT4102::Color::red},
    {TetrominoType::O, TDT4102::Color::yellow},
    {TetrominoType::I, TDT4102::Color::light_blue},
};


TetrisWindow::TetrisWindow() : AnimationWindow{startX,startY,Tetromino::blockSize * gridW,Tetromino::blockSize* gridH + 100,"Tetris"},
    currentTetromino{}, 
    gridMatrix{gridH, std::vector<TetrominoType>(gridW, TetrominoType::NONE)},
    gameOverTxt{{Tetromino::blockSize* gridW/4, startY}, Tetromino::blockSize * gridW/2, Tetromino::blockSize, "You Lost!"},
    pointsTxt{{gridW, gridH*  Tetromino::blockSize + gridH}, Tetromino::blockSize * gridW/2, Tetromino::blockSize,totalPointsTxt},
    highscoreTxt{{gridW, gridH*  Tetromino::blockSize + 3* gridH}, Tetromino::blockSize * gridW/2, Tetromino::blockSize,""},
    restartBtn{{Tetromino::blockSize* gridW/4, startY + Tetromino::blockSize * 2}, Tetromino::blockSize * gridW/2, Tetromino::blockSize, "Restart"}

{
    generateRandomTetromino();
    add(gameOverTxt);
    add(pointsTxt);
    add(highscoreTxt);
    add(restartBtn);
    restartBtn.setVisible(false);
    restartBtn.setCallback(std::bind(&TetrisWindow::restart, this));
    gameOverTxt.setVisible(false);
    loadHighscore();
} 

void TetrisWindow::run() {
    unsigned int framesSinceLastTetronimoMove = 0;
    const unsigned int framesPerTetronimoMove = 20;
    while(!should_close()) { 
        framesSinceLastTetronimoMove++;
        drawInitialMap();
        if (!checkGameOver()){
            if(framesSinceLastTetronimoMove >= framesPerTetronimoMove) {
                framesSinceLastTetronimoMove = 0;
                /********************************************************/
                //Kall moveTetrominoDown() her
                moveTetrominoDown();
                /********************************************************/
            }
            handleInput();
        }
            /********************************************************/
            //Kall draw-funksjonene her
        if (!checkGameOver()){
            drawCurrentTetromino();
        }
        drawGridMatrix();
        /********************************************************/
        next_frame();
    }
}

void TetrisWindow::handleInput() {

    static bool lastAKeyState = false;
    static bool lastDKeyState = false;
    static bool lastSpaceKeyState = false;
    static bool lastLeftKeyState = false;
    static bool lastRightKeyState = false;
    static bool lastDownKeyState = false;

    bool currentAKeyState = is_key_down(KeyboardKey::A);
    bool currentDKeyState = is_key_down(KeyboardKey::D);
    bool currentSpaceKeyState = is_key_down(KeyboardKey::SPACE);
    bool currentLeftKeyState = is_key_down(KeyboardKey::LEFT);
    bool currentRightKeyState = is_key_down(KeyboardKey::RIGHT);
    bool currentDownKeyState = is_key_down(KeyboardKey::DOWN);

    if(currentAKeyState && !lastAKeyState && canMoveLeft() ) {
        std::cout << "Hello from a\n";
        currentTetromino.moveLeft();
    }

    if(currentDKeyState && !lastDKeyState && canMoveRight() ) {
        std::cout << "Hello from d\n";
        currentTetromino.moveRight();
    }
    
    if(currentSpaceKeyState && !lastSpaceKeyState && canMoveDown()) {
        std::cout << "Hello from space\n";
        currentTetromino.moveDown();
    }

    if(currentLeftKeyState && !lastLeftKeyState) {
        std::cout << "Hello from left\n";
        currentTetromino.rotateCounterClockwise();
        if (hasCrashed()){
            currentTetromino.rotateClockwise();
        }
    }

    if(currentRightKeyState && ! lastRightKeyState) {
        std::cout << "Hello from right\n";
        currentTetromino.rotateClockwise();
        if (hasCrashed()){
            currentTetromino.rotateCounterClockwise();
        }
    }
    if(currentDownKeyState && !lastDownKeyState && canMoveDown()) {
        std::cout << "Hello from down\n";
        while (canMoveDown()){
            currentTetromino.moveDown();
        }
        totalPoints += 1;
        totalPointsTxt = "Points: " + std::to_string(totalPoints);
        pointsTxt.setText(totalPointsTxt);
    }


    lastAKeyState = currentAKeyState;
    lastDKeyState = currentDKeyState;
    lastSpaceKeyState = currentSpaceKeyState;
    lastLeftKeyState = currentLeftKeyState;
    lastRightKeyState = currentRightKeyState;
    lastDownKeyState = currentDownKeyState;
}

void TetrisWindow::generateRandomTetromino(){
    std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(0, 6);
    int randomTetrominoInt = distribution(generator);
    TetrominoType randomTetrominoType = static_cast<TetrominoType>(randomTetrominoInt);
    currentTetromino = {{Tetromino::blockSize*gridW/2 - Tetromino::blockSize/2,0}, randomTetrominoType};
}

void TetrisWindow::drawCurrentTetromino() {
    TDT4102::Point pos = currentTetromino.getPosition();
    int blockSize = Tetromino::blockSize;
    int matrixSize = currentTetromino.getMatrixSize();

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            TetrominoType type = currentTetromino.getBlock(i, j);
            if (type != TetrominoType::NONE) {
                TDT4102::Point blockPosition = {pos.x + j * blockSize, pos.y + i * blockSize};
                TDT4102::Color color = tetrominoColorMap[type];
                draw_rectangle(blockPosition, blockSize, blockSize, color);
            }
        }
    }
}


void TetrisWindow::moveTetrominoDown(){
    if (canMoveDown()) {
        currentTetromino.moveDown();
    } else {
        fastenTetromino(); 
        generateRandomTetromino();  
    }
}

void TetrisWindow::fastenTetromino() {
    TDT4102::Point position = currentTetromino.getPosition();
    int matrixSize = currentTetromino.getMatrixSize();

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int gridX = (position.x + j * Tetromino::blockSize) / Tetromino::blockSize;
                int gridY = (position.y + i * Tetromino::blockSize) / Tetromino::blockSize;
                gridMatrix[gridY][gridX] = currentTetromino.getBlock(i, j);
            }
        }
    }

    // Reset the current Tetromino
    currentTetromino = Tetromino{};
    removeFullRows();
}   

void TetrisWindow::drawGridMatrix(){
   for (int i = 0; i < gridH; i++){
        for (int j = 0; j < gridW; j++){    
           if (gridMatrix.at(i).at(j) != TetrominoType::NONE){
                draw_rectangle(TDT4102::Point{j * Tetromino::blockSize, i * Tetromino::blockSize}, Tetromino::blockSize, Tetromino::blockSize, tetrominoColorMap.at(gridMatrix.at(i).at(j)));
            }
        }
    }
}

bool TetrisWindow::hasCrashed(){
    int matrixSize = currentTetromino.getMatrixSize();
    TDT4102::Point currPos = currentTetromino.getPosition();

    int gridPosX = currPos.x / Tetromino::blockSize;
    int gridPosY = currPos.y / Tetromino::blockSize;

    
    for (int i = 0; i < matrixSize; i++){
        for (int j = 0; j < matrixSize; j++){
            if (currentTetromino.blockExcist(i,j)){
                int checkX = gridPosX + j;
                int checkY = gridPosY + i;

                if (checkX < 0 || checkX >= gridW || checkY >= gridH) {
                    return true;  
                }

                if (gridMatrix[checkY][checkX] != TetrominoType::NONE) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TetrisWindow::canMoveLeft() {
    TDT4102::Point newPosition = currentTetromino.getPosition();
    newPosition.x -= Tetromino::blockSize; 
    
    int matrixSize = currentTetromino.getMatrixSize();
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int gridX = (newPosition.x / Tetromino::blockSize) + j;
                int gridY = (newPosition.y / Tetromino::blockSize) + i;
                if (gridX < 0 || gridMatrix[gridY][gridX] != TetrominoType::NONE) {
                    return false;
                }
            }
        }
    }
    return true; 
}


bool TetrisWindow::canMoveRight() {
    TDT4102::Point newPosition = currentTetromino.getPosition();
    newPosition.x += Tetromino::blockSize;

    if (newPosition.x >= gridW * Tetromino::blockSize) {
        return false; 
    }

    int matrixSize = currentTetromino.getMatrixSize();
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int gridX = (newPosition.x / Tetromino::blockSize) + j;
                int gridY = (newPosition.y / Tetromino::blockSize) + i;

                if (gridMatrix[gridY][gridX] != TetrominoType::NONE) {
                    return false;
                }
            }
        }
    }
    return true; 
}

bool TetrisWindow::canMoveDown() {
    TDT4102::Point newPosition = currentTetromino.getPosition();
    newPosition.y += Tetromino::blockSize; 

    int gridPosY = newPosition.y / Tetromino::blockSize;
    int gridPosX = newPosition.x / Tetromino::blockSize;

    int matrixSize = currentTetromino.getMatrixSize();
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int checkX = gridPosX + j;
                int checkY = gridPosY + i;

                if (checkY >= gridH) {
                    return false; 
                }

                if (gridMatrix[checkY][checkX] != TetrominoType::NONE) {
                    return false;
                }
            }
        }
    }
    return true; 
}


void TetrisWindow::removeFullRows() {
    int rowsRemoved{0};
    for (int row = gridH - 1; row >= 0; row--) {
        bool rowIsFull = true;
        for (int col = 0; col < gridW; col++) {
            if (gridMatrix[row][col] == TetrominoType::NONE) {
                rowIsFull = false;
                break;
            }
        }

        if (rowIsFull) {
            rowsRemoved++;
            for (int row_above = row; row_above > 0; row_above--) {
                for (int col = 0; col < gridW; col++) {
                    gridMatrix[row_above][col] = gridMatrix[row_above - 1][col];
                }
            }
            for (int col = 0; col < gridW; col++) {
                gridMatrix[0][col] = TetrominoType::NONE;
            }
            row++;
        }
    }
    if (rowsRemoved == 1){
        totalPoints += 40;
    } else if (rowsRemoved == 2){
        totalPoints += 100;
    } else if (rowsRemoved == 3){
        totalPoints += 300;
    } else if (rowsRemoved == 4){
        totalPoints += 1200;
    }
    totalPointsTxt = "Points: " + std::to_string(totalPoints);
    pointsTxt.setText(totalPointsTxt);
}

bool TetrisWindow::checkGameOver() {
    int matrixSize = currentTetromino.getMatrixSize();
    TDT4102::Point pos = currentTetromino.getPosition();
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int gridX = (pos.x + j * Tetromino::blockSize) / Tetromino::blockSize;
                int gridY = (pos.y + i * Tetromino::blockSize) / Tetromino::blockSize;
                if (gridMatrix[gridY][gridX] != TetrominoType::NONE) {    
                    gameOverTxt.setVisible(true);
                    saveHighscore();
                    restartBtn.setVisible(true);
                    return true; 
                }
            }
        }
    }
    return false;
}

void TetrisWindow::saveHighscore()
{
    if (totalPoints > highScore){
        std::fstream f;
        f.open("highScore.txt", std::ios::out);
        if (f.is_open()){
            f << totalPoints;  
        }
    }
}

void TetrisWindow::loadHighscore(){
    std::fstream f;
    f.open("highScore.txt", std::ios::in);
    if (f.is_open()){
        std::string higestScore;
        while (getline(f, higestScore)){
            highscoreTxt.setText("HighScore: " + higestScore);
            highScore = stoi(higestScore);
        }
    }
}

void TetrisWindow::restart(){
    for (int row = 0; row < gridH; row++)
    {
        for (int col = 0; col < gridW; col++)
        {
            gridMatrix[row][col] = TetrominoType::NONE;
        }
    }
    totalPoints = 0;
    restartBtn.setVisible(false);
    gameOverTxt.setVisible(false);
    totalPointsTxt = "Points: " + std::to_string(totalPoints);
    pointsTxt.setText(totalPointsTxt);
    loadHighscore();    
}

void TetrisWindow:: drawInitialMap(){
   for (int i = 0; i < gridH; i++){
        for (int j = 0; j < gridW; j++){    
           if (gridMatrix.at(i).at(j) == TetrominoType::NONE){
                draw_rectangle(TDT4102::Point{j * Tetromino::blockSize, i * Tetromino::blockSize}, Tetromino::blockSize, Tetromino::blockSize, tetrominoColorMap.at(gridMatrix.at(i).at(j)));
            }
        }
    }
}