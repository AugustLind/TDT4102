#pragma once
#include "AnimationWindow.h"
#include "Tetromino.h"
#include "widgets/TextInput.h"
#include <vector>
#include "widgets/Button.h"

class TetrisWindow : public TDT4102::AnimationWindow {

public:
    TetrisWindow();
    void run();
    void generateRandomTetromino();
    void drawCurrentTetromino();
    void moveTetrominoDown();
    void fastenTetromino();
    void drawGridMatrix();
    bool hasCrashed(); 
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    void removeFullRows();
    bool checkGameOver();
    void saveHighscore();
    void loadHighscore();
    void restart();
    void drawInitialMap();

private:
 
    void handleInput();
    static constexpr int startX{250};
    static constexpr int startY{250};
    static constexpr int height{500};
    static constexpr int width{300};
    static constexpr int gridH{20};
    static constexpr int gridW{15}; 
    std::vector<std::vector<TetrominoType>> gridMatrix;
    Tetromino currentTetromino;
    TDT4102::TextInput gameOverTxt;
    int totalPoints{0};
    std::string totalPointsTxt = "Points: " + std::to_string(totalPoints);
    TDT4102::TextInput pointsTxt;
    int highScore{0};
    TDT4102::TextInput highscoreTxt;
    TDT4102::Button restartBtn;
};