#pragma once


#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Game {
private:
    Board board;
    bool isGameOver;
    bool isWin;

    sf::RenderWindow window;  // Game window for SFML rendering

public:
    Game(int rows, int cols, int mines);

    void startGame();
    void checkWin();
    void revealCell(int row, int col);
    void flagCell(int row, int col);

    void run();
};

