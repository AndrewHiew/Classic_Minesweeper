#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Cell {
private:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;

    sf::Sprite sprite;
    sf::Texture texture;

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

    void setTexture(const sf::Texture& tex);
    void setTextureRect(const sf::IntRect& rect);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
};
