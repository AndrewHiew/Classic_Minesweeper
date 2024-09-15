#pragma once
#include "Game.h"

int main() {
    // Create a game instance
    Game game(10, 10, 10);  // 10x10 grid with 10 mines
    game.run();

    return 0;
}