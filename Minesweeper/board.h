#pragma once

#include "Cell.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Board {
private:
    int numRows;
    int numCols;
    int numMines;
    vector<vector<Cell>> grid;
    sf::Texture tilesTexture;

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

    void draw(sf::RenderWindow& window);  // Draw the entire board
    pair<int, int> getCellFromPosition(float x, float y); // Get cell based on mouse click
};

