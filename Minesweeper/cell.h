#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Cell {
private:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;

    Sprite sprite;
    Texture texture;

public:
    Cell();

    bool getIsMine() const;
    void setIsMine(bool mine);

    bool getIsRevealed() const;
    void reveal();

    bool getIsFlagged() const;
    void toggleFlag();

    int getAdjacentMines() const;
    void setAdjacentMines(int mines);

    void setTexture(const Texture& tex);
    void setTextureRect(const IntRect& rect);
    void setPosition(float x, float y);
    void draw(RenderWindow& window);

    void updateTexture(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture);
};
