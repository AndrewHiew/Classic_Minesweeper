#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Game {
public:
    Game(int rows, int cols, int mines);
    void startGame();

private:
    Board board;
    bool isGameOver;
    bool isWin;
    RenderWindow window;
    RectangleShape restartButton;
    Text restartButtonText;
    Font font;
    bool leftButtonPressed;
    bool rightButtonPressed;

    void revealCell(int row, int col);
    void flagCell(int row, int col);
    void checkWin();
    void checkLose();
    void revealSurroundingCell(pair<int, int> centerCell);
    void initializeButton();
    void handleButtonClick(Vector2i mousePosition);
    void resetGame();
    void drawButton();
};