#pragma once

#include "Board.h"
#include <random>
#include <iostream>


using namespace std;

Board::Board(int rows, int cols, int mines) : numRows(rows), numCols(cols), numMines(mines) {
    grid = vector<vector<Cell>>(numRows, vector<Cell>(numCols));
    mineFlagged = 0;
    isMineClicked = false;

    loadTextures();
    generateMines();
    generateBoard();
}

void Board::loadTextures() {
    if (!tileTexture.loadFromFile("normal-tile.png") ||
        !flagTexture.loadFromFile("flag-tile.png") ||
        !mineTexture.loadFromFile("mine-tile.png") ||
        !revealedTexture.loadFromFile("revealed-tile.png") ||
        !clickedMineTexture.loadFromFile("clicked-mine-tile.png") ||
        !tileTexture1.loadFromFile("1-tile.png") ||
        !tileTexture2.loadFromFile("2-tile.png") ||
        !tileTexture3.loadFromFile("3-tile.png") ||
        !tileTexture4.loadFromFile("4-tile.png") ||
        !tileTexture5.loadFromFile("5-tile.png") ||
        !tileTexture6.loadFromFile("6-tile.png") ||
        !tileTexture7.loadFromFile("7-tile.png") ||
        !tileTexture8.loadFromFile("8-tile.png")) {
        throw std::runtime_error("Failed to load textures");
    }
}

// Method to draw the board and setting the tile textures
void Board::draw(RenderWindow& window) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            grid[row][col].setPosition(col * 32, row * 32);
            grid[row][col].updateTexture(tileTexture, flagTexture, mineTexture, revealedTexture, clickedMineTexture
                , tileTexture1, tileTexture2, tileTexture3, tileTexture4
                , tileTexture5, tileTexture6, tileTexture7, tileTexture8);

            grid[row][col].draw(window);
        }
    }
}


// Method to draw the board and setting the tile textures, when the game ends either by winning or losing.
void Board::revealAllCells(RenderWindow& window) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            grid[row][col].setPosition(col * 32, row * 32);
            grid[row][col].revealAll(tileTexture, flagTexture, mineTexture, revealedTexture, clickedMineTexture
                , tileTexture1, tileTexture2, tileTexture3, tileTexture4
                , tileTexture5, tileTexture6, tileTexture7, tileTexture8);

            grid[row][col].draw(window);
        }
    }
}

bool Board::getIsMineClicked() {
    return isMineClicked;
}

int Board::getMineFlagged() {
    return mineFlagged;
}

int Board::getNumMines() {
    return numMines;
}

Cell& Board::getCell(int row, int col) {
    if (isValidCell(row, col)) {
        return grid[row][col];
    }
    else {
        throw out_of_range("Invalid cell coordinates");
    }
}


// Method to generate random mines
void Board::generateMines() {
    int placedMines = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distRow(0, numRows - 1);
    uniform_int_distribution<> distCol(0, numCols - 1);

    while (placedMines < numMines) {
        int row = distRow(gen);
        int col = distCol(gen);

        if (!grid[row][col].getIsMine()) {
            grid[row][col].setIsMine(true);
            ++placedMines;
        }
    }
}

void Board::generateBoard() {
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
    if (!isValidCell(row, col) || grid[row][col].getIsRevealed() || grid[row][col].getIsFlagged()) {
        return;
    }

    grid[row][col].reveal();

    // If the cell is a mine, the game is over.
    if (grid[row][col].getIsMine()) {
        isMineClicked = true;
        return;
    }

    if (grid[row][col].getAdjacentMines() == 0) {
        // Recursively reveal neighboring cells
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                if (r != 0 || c != 0) {
                    revealCell(row + r, col + c);
                }
            }
        }
    }
}


void Board::flagCell(int row, int col) {
    if (isValidCell(row, col) && !grid[row][col].getIsRevealed()) {
        grid[row][col].toggleFlag();
        if (grid[row][col].getIsMine()) {
            mineFlagged += 1;
        }
        cout << "Debug (Flag mine): " << mineFlagged << endl;
    }
}

int Board::getAdjacentMines(int row, int col) const{
    return grid[row][col].getAdjacentMines();
}

bool Board::isMine(int row, int col) const {
    return grid[row][col].getIsMine();
}


pair<int, int> Board::getCellFromPosition(float x, float y) {
    // 32 pixels cell
    int row = static_cast<int>(y) / 32;
    int col = static_cast<int>(x) / 32;

    // out of bound exception handler
    if (isValidCell(row, col)) {
        return { row, col };
    }
    else {
        return { -1, -1 };
    }
}