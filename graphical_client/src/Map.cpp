/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "Map.hpp"
#include "Singleton.hpp"

Map::Map(int width, int height) : width(width), height(height)
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
        for (auto &it2 : it->getSprites()) {
            SingleTon<sf::RenderWindow>::getInstance().draw(it2);
        }
    }
}

std::unique_ptr<Tile> &Map::getTileAtCoord(int x, int y)
{
    auto tile = std::find_if(this->tiles.begin(), this->tiles.end(), [x, y](std::unique_ptr<Tile> &tile) {
        std::pair<int, int> pos = tile->getPosition();
        return pos.first == x && pos.second == y;
    });
    if (tile == this->tiles.end()) {
        throw std::out_of_range("out of bounds");
    }
    return *tile;
}