#include "Game.h"
#include <Windows.h>
#include <iostream>

using namespace sf;
using namespace std;

Game::Game(int rows, int cols, int mines)
    : board(rows, cols, mines), isGameOver(false), isWin(false),
    window(sf::VideoMode(480, 560), "Classic Minesweeper") {
    initializeButton(); // Initialize the button when the game starts
}

void Game::initializeButton() {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font" << endl;
    }

    // Setup restart button
    restartButton.setSize(Vector2f(150, 50));
    restartButton.setFillColor(Color::Cyan);
    restartButton.setPosition(window.getSize().x - 160, window.getSize().y - 60);

    // Setup button text
    restartButtonText.setFont(font);
    restartButtonText.setString("Restart");
    restartButtonText.setCharacterSize(20);
    restartButtonText.setFillColor(Color::White);
    restartButtonText.setPosition(restartButton.getPosition().x + 10, restartButton.getPosition().y + 10);
}

void Game::handleButtonClick(Vector2i mousePosition) {
    if (restartButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition))) {
        resetGame();
    }
}

void Game::resetGame() {
    board.reset();
    isGameOver = false;
    isWin = false;
}

void Game::drawButton() {
    if (isGameOver) {
        window.draw(restartButton);
        window.draw(restartButtonText);
    }
}

void Game::revealCell(int row, int col) {
    if (!isGameOver) {
        board.revealCell(row, col);
    }
}

void Game::flagCell(int row, int col) {
    if (!isGameOver) {
        board.flagCell(row, col);
    }
}

void Game::checkWin() {
    if (board.areAllMinesCorrectlyFlagged()) {
        isWin = true;
        isGameOver = true;
        MessageBox(nullptr, L"Congratulations, you won!", L"Game Over", MB_OK);
    }
}

void Game::checkLose() {
    if (!isGameOver) {
        window.clear();
        board.revealAllCells(window);
        window.display();
        isGameOver = true;
        MessageBox(nullptr, L"Game Over! You lost.", L"Game Over", MB_OK);
    }
}

void Game::revealSurroundingCell(pair<int, int> centerCell) {
    if (centerCell.first != -1 && centerCell.second != -1 && board.getCell(centerCell.first, centerCell.second).getIsRevealed()) {
        int adjacentMines = board.getAdjacentMines(centerCell.first, centerCell.second);

        int flagCount = 0;
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int newRow = centerCell.first + r;
                int newCol = centerCell.second + c;

                if (board.isValidCell(newRow, newCol)) {
                    if (board.getCell(newRow, newCol).getIsFlagged()) {
                        flagCount++;
                    }
                }
            }
        }

        if (flagCount == adjacentMines) {
            for (int r = -1; r <= 1; ++r) {
                for (int c = -1; c <= 1; ++c) {
                    int newRow = centerCell.first + r;
                    int newCol = centerCell.second + c;

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
        // Event Handling
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
                    pair<int, int> centerCell = board.getCellFromPosition(eventHandler.mouseButton.x, eventHandler.mouseButton.y);
                    this->revealSurroundingCell(centerCell);
                }

                // Check for button click
                handleButtonClick(sf::Vector2i(eventHandler.mouseButton.x, eventHandler.mouseButton.y));
            }
        }

        if (!isGameOver) {
            // Game Ending logic either by winning or losing
            if (board.getIsMineClicked()) {
                checkLose();
            }
            else if (board.areAllMinesCorrectlyFlagged()) {
                checkWin();
            }
        }

        // Drawing the board and button
        window.clear();
        board.draw(window);
        drawButton();
        window.display();
    }
}
