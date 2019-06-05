/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include "Tile.hpp"

Tile::Tile(int x, int y) : x(x), y(y)
{
    bool toto = this->texture.loadFromFile("assets/Grass.png");
    if (!toto)
    {
        std::cout << "BITE de chien !!!!" << std::endl;
    }
    this->sprite.setTexture(texture);
    this->sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

sf::Sprite &Tile::getSprite()
{
    return this->sprite;
}