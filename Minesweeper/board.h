#pragma once

#include "Cell.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Board {
private:
    int numRows;
    int numCols;
    int numMines;
    int mineFlagged;
    bool isMineClicked;

    vector<vector<Cell>> grid;

    Texture tileTexture;
    Texture flagTexture;
    Texture mineTexture;
    Texture revealedTexture;
    Texture clickedMineTexture;
    Texture tileTexture1;
    Texture tileTexture2;
    Texture tileTexture3;
    Texture tileTexture4;
    Texture tileTexture5;
    Texture tileTexture6;
    Texture tileTexture7;
    Texture tileTexture8;

    void generateMines();

public:
    Board(int rows, int cols, int mines);

    void generateBoard();
    void revealCell(int row, int col);
    void flagCell(int row, int col);

    bool getIsMineClicked();
    int getMineFlagged();
    int getNumMines();
    bool areAllMinesCorrectlyFlagged();
    int getAdjacentMines(int row, int col) const;
    bool isValidCell(int row, int col) const;
    bool isMine(int row, int col) const;
    Cell& getCell(int row, int col);
    void reset();

    // Method to draw the entire board
    void draw(RenderWindow& window);

    // Method to reveal all cells by winning or losing the game
    void revealAllCells(RenderWindow& window);

    // Get cells based on mouse click
    pair<int, int> getCellFromPosition(float x, float y);

    void loadTextures();
};
