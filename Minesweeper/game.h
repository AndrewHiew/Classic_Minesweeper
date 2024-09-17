#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

class Game {
private:
    Board board;               
    bool isGameOver;           
    bool isWin;                

    RenderWindow window;
    Texture tilesTexture;

public:
    // Constructor
    Game(int rows, int cols, int mines);

    // Game logic methods
    void checkLose();
    void checkWin();
    void revealSurroundingCell(pair<int, int> centerCell);
    void revealCell(int row, int col);
    void flagCell(int row, int col);

    // Main game loop
    void startGame();
};
