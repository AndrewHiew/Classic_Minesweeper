#pragma once

#include "Cell.h"

Cell::Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0) { }

bool Cell::getIsMine() const { return isMine; }
void Cell::setIsMine(bool mine) { isMine = mine; }

bool Cell::getIsRevealed() const { return isRevealed; }
void Cell::reveal() { isRevealed = true; }

bool Cell::getIsFlagged() const { return isFlagged; }
void Cell::toggleFlag() { isFlagged = !isFlagged; }

int Cell::getAdjacentMines() const { return adjacentMines; }
void Cell::setAdjacentMines(int mines) { adjacentMines = mines; }

void Cell::setTexture(const sf::Texture& tex) {
    texture = tex;
    sprite.setTexture(texture);
}

void Cell::setTextureRect(const sf::IntRect& rect) {
    sprite.setTextureRect(rect);
}

void Cell::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Cell::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
