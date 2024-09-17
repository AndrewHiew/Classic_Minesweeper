#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;

Game::Game(int rows, int cols, int mines)
    : board(rows, cols, mines), isGameOver(false), isWin(false),
    window(sf::VideoMode(480, 480), "Classic Minesweeper") {
}

void Game::revealCell(int row, int col) {
    board.revealCell(row, col);
}

void Game::flagCell(int row, int col) {
    board.flagCell(row, col);
}

void Game::checkWin() {

}

void Game::checkLose() {
    window.clear();
    board.revealAllCells(window);
    window.display();
}

void Game::revealSurroundingCell(pair<int, int> centerCell) {
    // Check if the cell is valid and revealed
    if (centerCell.first != -1 && centerCell.second != -1 && board.getCell(centerCell.first, centerCell.second).getIsRevealed()) {

        // Get the number on the clicked cell (adjacent mines)
        int adjacentMines = board.getAdjacentMines(centerCell.first, centerCell.second);

        // Count the flags around the clicked cell
        int flagCount = 0;
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int newRow = centerCell.first + r;
                int newCol = centerCell.second + c;

                // Check if the cell is valid
                if (board.isValidCell(newRow, newCol)) {
                    // Increment flagCount if the cell is flagged
                    if (board.getCell(newRow, newCol).getIsFlagged()) {
                        flagCount++;
                    }
                }
            }
        }

        // Only reveal if the number of flags matches the number of adjacent mines
        if (flagCount == adjacentMines) {
            // Loop through the 3x3 grid centered on the clicked cell and reveal non-flagged cells
            for (int r = -1; r <= 1; ++r) {
                for (int c = -1; c <= 1; ++c) {
                    int newRow = centerCell.first + r;
                    int newCol = centerCell.second + c;

                    // Reveal the cell if it's valid and not flagged
                    if (board.isValidCell(newRow, newCol) && !board.getCell(newRow, newCol).getIsFlagged()) {
                        board.revealCell(newRow, newCol);
                    }
                }
            }
        }
    }
}

void Game::startGame() {
    while (window.isOpen()) {
        while (board.getIsMineClicked() || (board.getNumMines() != board.getMineFlagged())) {
            cout << "Debug 1: " << board.getIsMineClicked() << endl;

            // Game Ending logic either by winning or losing
            if (board.getIsMineClicked()) {
                checkLose();
                break;
            }

            if (board.getNumMines() == board.getMineFlagged()) {
                checkWin();
                break;
            }


            // Event Handler Section
            Event eventHandler;

            while (window.pollEvent(eventHandler)) {
                if (eventHandler.type == Event::Closed) {
                    window.close();
                }

                if (eventHandler.type == Event::MouseButtonPressed) {
                    if (eventHandler.mouseButton.button == Mouse::Left) {
                        pair<int, int> cell = board.getCellFromPosition(eventHandler.mouseButton.x, eventHandler.mouseButton.y);
                        if (cell.first != -1 && cell.second != -1) {
                            revealCell(cell.first, cell.second);
                        }
                    }

                    if (eventHandler.mouseButton.button == Mouse::Right) {
                        pair<int, int> cell = board.getCellFromPosition(eventHandler.mouseButton.x, eventHandler.mouseButton.y);
                        if (cell.first != -1 && cell.second != -1) {
                            flagCell(cell.first, cell.second);
                        }
                    }

                    if (eventHandler.mouseButton.button == Mouse::Left && Mouse::isButtonPressed(Mouse::Right)) {
                        // Get the clicked cell's coordinates
                        pair<int, int> centerCell = board.getCellFromPosition(eventHandler.mouseButton.x, eventHandler.mouseButton.y);
                        this->revealSurroundingCell(centerCell);
                    }

                }
            }

            // Drawing the board Section
            window.clear();
            board.draw(window);
            window.display();
        }
    }
}
