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
    vector<vector<Cell>> grid;

    Texture tileTexture;
    Texture flagTexture;
    Texture mineTexture;
    Texture revealedTexture;

    void generateMines();
    void calculateAdjacentMines();

public:
    Board(int rows, int cols, int mines);

    void generateBoard();
    void revealCell(int row, int col);
    void flagCell(int row, int col);

    int getAdjacentMines(int row, int col) const;
    bool isValidCell(int row, int col) const;
    bool isMine(int row, int col) const;
    Cell& getCell(int row, int col);

    void draw(RenderWindow& window);  // Draw the entire board
    pair<int, int> getCellFromPosition(float x, float y); // Get cell based on mouse click

    void loadTextures();
};
