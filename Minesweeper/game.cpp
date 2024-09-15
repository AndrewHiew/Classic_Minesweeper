#include "Game.h"
using namespace std;

Game::Game(int rows, int cols, int mines)
    : board(rows, cols, mines), isGameOver(false), isWin(false),
    window(sf::VideoMode(640, 480), "Minesweeper") {
}

void Game::revealCell(int row, int col) {
    board.revealCell(row, col);
}

void Game::flagCell(int row, int col) {
    board.flagCell(row, col);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Explicitly declare the pair type for row and col
                    std::pair<int, int> cell = board.getCellFromPosition(event.mouseButton.x, event.mouseButton.y);
                    int row = cell.first;
                    int col = cell.second;

                    if (row != -1 && col != -1) {
                        revealCell(row, col);
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // Explicitly declare the pair type for row and col
                    std::pair<int, int> cell = board.getCellFromPosition(event.mouseButton.x, event.mouseButton.y);
                    int row = cell.first;
                    int col = cell.second;

                    if (row != -1 && col != -1) {
                        flagCell(row, col);
                    }
                }
            }
        }

        window.clear();
        board.draw(window);  // Draw the entire board
        window.display();    // Display everything on the screen
    }
}
