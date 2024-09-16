#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Game {
private:
    Board board;               
    bool isGameOver;           
    bool isWin;                

    sf::RenderWindow window;
    sf::Texture tilesTexture;

public:
    // Constructor
    Game(int rows, int cols, int mines);

    // Game logic methods
    void startGame();
    void checkWin();
    void revealCell(int row, int col);
    void flagCell(int row, int col);

    // Main game loop
    void run();
};
