#include "Cell.h"
# include <iostream>
using namespace std;

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

// Method to update the cell Texture when triggered by either winning or losing the game
void Cell::revealAll(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture, const Texture& clickedMineTexture
    , const Texture& tileTexture1, const Texture& tileTexture2, const Texture& tileTexture3, const Texture& tileTexture4
    , const Texture& tileTexture5, const Texture& tileTexture6, const Texture& tileTexture7, const Texture& tileTexture8) {
    
    if (isMine) {
        sprite.setTexture(mineTexture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
    }
    else {
        if (adjacentMines != 0) {
            switch (adjacentMines) {
            case 1:
                sprite.setTexture(tileTexture1);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 2:
                sprite.setTexture(tileTexture2);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 3:
                sprite.setTexture(tileTexture3);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 4:
                sprite.setTexture(tileTexture4);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 5:
                sprite.setTexture(tileTexture5);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 6:
                sprite.setTexture(tileTexture6);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 7:
                sprite.setTexture(tileTexture7);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            case 8:
                sprite.setTexture(tileTexture8);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
                break;
            default:
                cout << "Adjacent Mines (cell class): " << adjacentMines << endl;
            }
        }
        else {
            sprite.setTexture(revealedTexture);
            sprite.setTextureRect(IntRect(0, 0, 32, 32));
        }
    }
}

// Method to update the cell Texture when triggered by mouse event
void Cell::updateTexture(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture, const Texture& clickedMineTexture
    , const Texture& tileTexture1, const Texture& tileTexture2, const Texture& tileTexture3, const Texture& tileTexture4
    , const Texture& tileTexture5, const Texture& tileTexture6, const Texture& tileTexture7, const Texture& tileTexture8) {
    if (isRevealed) {
        if (isMine) {
            sprite.setTexture(clickedMineTexture);
            sprite.setTextureRect(IntRect(0, 0, 32, 32));
        }
        else {
            if (adjacentMines != 0) {
                switch (adjacentMines) {
                    case 1:
                        sprite.setTexture(tileTexture1);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 2:
                        sprite.setTexture(tileTexture2);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 3:
                        sprite.setTexture(tileTexture3);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 4:
                        sprite.setTexture(tileTexture4);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 5:
                        sprite.setTexture(tileTexture5);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 6:
                        sprite.setTexture(tileTexture6);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 7:
                        sprite.setTexture(tileTexture7);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 8:
                        sprite.setTexture(tileTexture8);
                        sprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    default:
                        cout << "Adjacent Mines (cell class): " << adjacentMines << endl;
                }
            }
            else {
                sprite.setTexture(revealedTexture);
                sprite.setTextureRect(IntRect(0, 0, 32, 32));
            }
        }
    }
    else if (isFlagged) {
        sprite.setTexture(flagTexture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
    }
    else {
        sprite.setTexture(tileTexture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
    }
}
