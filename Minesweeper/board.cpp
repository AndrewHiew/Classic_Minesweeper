#pragma once

#include "Board.h"
#include <random>

Board::Board(int rows, int cols, int mines) : numRows(rows), numCols(cols), numMines(mines) {
    grid = vector<vector<Cell>>(numRows, vector<Cell>(numCols));
    generateBoard();
}

void Board::draw(sf::RenderWindow& window) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            grid[row][col].draw(window);
        }
    }
}



void Board::generateBoard() {
    int placedMines = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disRow(0, numRows - 1);
    uniform_int_distribution<> disCol(0, numCols - 1);

    while (placedMines < numMines) {
        int row = disRow(gen);
        int col = disCol(gen);

        if (!grid[row][col].getIsMine()) {
            grid[row][col].setIsMine(true);
            ++placedMines;
        }
    }

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (!grid[row][col].getIsMine()) {
                int adjacentMines = 0;


                for (int r = -1; r <= 1; ++r) {
                    for (int c = -1; c <= 1; ++c) {
                        if (isValidCell(row + r, col + c) && grid[row + r][col + c].getIsMine()) {
                            ++adjacentMines;
                        }
                    }
                }
                grid[row][col].setAdjacentMines(adjacentMines);
            }
        }
    }
}


bool Board::isValidCell(int row, int col) const {
    return (row >= 0 && row < numRows && col >= 0 && col < numCols);
}

void Board::revealCell(int row, int col) {
    if (isValidCell(row, col) && !grid[row][col].getIsRevealed()) {
        grid[row][col].reveal();

        if (!grid[row][col].getIsMine()) {
            if (grid[row][col].getAdjacentMines() == 0) {
                for (int r = -1; r <= 1; ++r) {
                    for (int c = -1; c <= 1; ++c) {
                        if (r != 0 || c != 0) {
                            revealCell(row + r, col + c);
                        }
                    }
                }
            }
        }
    }
}

void Board::flagCell(int row, int col) {
    if (isValidCell(row, col) && !grid[row][col].getIsRevealed()) {
        grid[row][col].toggleFlag();
    }
}


pair<int, int> Board::getCellFromPosition(float x, float y) {
    int col = static_cast<int>(x / 32);
    int row = static_cast<int>(y / 32);
    if (isValidCell(row, col)) {
        return { row, col };
    }
    return { -1, -1 };
}
