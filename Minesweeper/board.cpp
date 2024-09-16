#pragma once

#include "Board.h"
#include <random>

Board::Board(int rows, int cols, int mines) : numRows(rows), numCols(cols), numMines(mines) {
    grid = vector<vector<Cell>>(numRows, vector<Cell>(numCols));
    loadTextures();
    generateBoard();
}

void Board::loadTextures() {
    if (!tileTexture.loadFromFile("normal-tile.png") ||
        !flagTexture.loadFromFile("flag-tile.png") ||
        !mineTexture.loadFromFile("mine-tile.png") ||
        !revealedTexture.loadFromFile("revealed-tile.png")) {
        throw std::runtime_error("Failed to load textures");
    }
}

void Board::draw(RenderWindow& window) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            grid[row][col].setPosition(col * 32, row * 32);
            grid[row][col].updateTexture(tileTexture, flagTexture, mineTexture, revealedTexture);
            grid[row][col].draw(window);
        }
    }
}

Cell& Board::getCell(int row, int col) {
    if (isValidCell(row, col)) {
        return grid[row][col];
    }
    else {
        throw std::out_of_range("Invalid cell coordinates");
    }
}

void Board::generateBoard() {
    // Place mines randomly
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

    // Calculate adjacent mines for non-mine cells
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (!grid[row][col].getIsMine()) {
                int adjacentMines = 0;

                // Check all surrounding cells for mines
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

        // Set the correct sprite based on the cell’s state
        if (grid[row][col].getIsMine()) {
            grid[row][col].setTextureRect(sf::IntRect(128, 0, 16, 16));  // Mine tile
        }
        else {
            int adjacentMines = grid[row][col].getAdjacentMines();
            if (adjacentMines > 0) {
                grid[row][col].setTextureRect(sf::IntRect(16 * (adjacentMines - 1), 0, 16, 16));  // "1" to "8" tiles
            }
            else {
                grid[row][col].setTextureRect(sf::IntRect(0, 0, 16, 16));  // Empty tile for no adjacent mines
            }
        }
    }
}

void Board::flagCell(int row, int col) {
    if (isValidCell(row, col) && !grid[row][col].getIsRevealed()) {
        grid[row][col].toggleFlag();

        if (grid[row][col].getIsFlagged()) {
            grid[row][col].setTextureRect(sf::IntRect(144, 0, 16, 16));  // Flag tile
        }
        else {
            // Reset to unrevealed tile
            grid[row][col].setTextureRect(sf::IntRect(0, 0, 16, 16));  // Unrevealed state (optional)
        }
    }
}

int Board::getAdjacentMines(int row, int col) const{
    return 0;
}

bool Board::isMine(int row, int col) const {
    return true;
}

pair<int, int> Board::getCellFromPosition(float x, float y) {
    int row = static_cast<int>(y) / 32;  // Assuming each cell is 32x32 pixels
    int col = static_cast<int>(x) / 32;

    if (isValidCell(row, col)) {
        return { row, col };
    }
    else {
        return { -1, -1 };  // Return invalid coordinates if out of bounds
    }
}