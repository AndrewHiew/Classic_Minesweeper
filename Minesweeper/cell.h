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
    void reset();

    // Method to update the cell Texture when triggered by either winning or losing the game
    void revealAll(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture, const Texture& clickedMineTexture
        , const Texture& tileTextuire1, const Texture& tileTextuire2, const Texture& tileTextuire3, const Texture& tileTextuire4
        , const Texture& tileTextuire5, const Texture& tileTextuire6, const Texture& tileTextuire7, const Texture& tileTextuire8);

    // Method to update the cell Texture when triggered by mouse event
    void updateTexture(const Texture& tileTexture, const Texture& flagTexture, const Texture& mineTexture, const Texture& revealedTexture, const Texture& clickedMineTexture
        , const Texture& tileTextuire1, const Texture& tileTextuire2, const Texture& tileTextuire3, const Texture& tileTextuire4
        , const Texture& tileTextuire5, const Texture& tileTextuire6, const Texture& tileTextuire7, const Texture& tileTextuire8);
};
