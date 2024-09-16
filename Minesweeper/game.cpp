#include "Game.h"
#include <iostream>

Game::Game(int rows, int cols, int mines)
    : board(rows, cols, mines), isGameOver(false), isWin(false),
    window(sf::VideoMode(600, 600), "Minesweeper") {

    // Load texture from the file
    // Note: textures are now loaded in Board class
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
                    std::pair<int, int> cell = board.getCellFromPosition(event.mouseButton.x, event.mouseButton.y);
                    if (cell.first != -1 && cell.second != -1) {
                        revealCell(cell.first, cell.second);
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::pair<int, int> cell = board.getCellFromPosition(event.mouseButton.x, event.mouseButton.y);
                    if (cell.first != -1 && cell.second != -1) {
                        flagCell(cell.first, cell.second);
                    }
                }
            }
        }

        window.clear();
        board.draw(window);  // Draw the entire board
        window.display();
    }
}
