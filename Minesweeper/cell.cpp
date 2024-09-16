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

void Cell::setTexture(const Texture& tex) {
    texture = tex;
    sprite.setTexture(texture);
}

void Cell::setTextureRect(const IntRect& rect) {
    sprite.setTextureRect(rect);
}

void Cell::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Cell::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Cell::updateTexture(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture) {
    if (isRevealed) {
        if (isMine) {
            sprite.setTexture(mineTexture);
            sprite.setTextureRect(IntRect(0, 0, 32, 32)); // Adjust based on texture size
        }
        else {
            int adjacentMines = getAdjacentMines();
            sprite.setTexture(revealedTexture);
            sprite.setTextureRect(IntRect(32 * adjacentMines, 0, 32, 32)); // Adjust based on texture size
        }
    }
    else if (isFlagged) {
        sprite.setTexture(flagTexture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32)); // Adjust based on texture size
    }
    else {
        sprite.setTexture(tileTexture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32)); // Adjust based on texture size
    }
}
