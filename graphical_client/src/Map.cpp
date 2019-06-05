/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "Map.hpp"

Map::Map(int width, int height, sf::RenderWindow &window) : width(width), height(height), window(window)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->tiles.emplace_back(new Tile(j, i));
        }
    }
}

void Map::draw()
{
    for (auto &it : this->tiles) {
        this->window.draw(it->getSprite());
    }
}
