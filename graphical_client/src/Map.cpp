/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include "Map.hpp"
#include "Singleton.hpp"
#include "Responsive.hpp"
#include "TextureLoader.hpp"

Map::Map(int width, int height) : width(width), height(height), tileSize(Responsive::calcTileSize(width, height))
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            this->tiles.emplace_back(new Tile(j, i, Responsive::calcTileSize(width, height)));
}

void Map::draw()
{
    for (auto &it : this->tiles) {
        for (auto &it2 : it->getSprites()) {
            SingleTon<sf::RenderWindow>::getInstance().draw(it2);
        }
    }
    drawIncantations();
}

std::shared_ptr<Tile> &Map::getTileAtCoord(int x, int y)
{
    auto tile = std::find_if(this->tiles.begin(), this->tiles.end(), [x, y](std::shared_ptr<Tile> &tile) {
        auto pos = tile->getPosition();
        return pos.x == x && pos.y == y;
    });
    if (tile == this->tiles.end()) {
        throw std::out_of_range("out of bounds");
    }
    return *tile;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

const std::vector<std::shared_ptr<Tile>> &Map::getTiles() const
{
    return tiles;
}

void Map::addIncantationSprite(const Position &pos)
{
    sf::Sprite sprite;

    sprite.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/incantation.png"));
    sprite.setPosition(pos.x * tileSize, pos.y * tileSize);
    sprite.setScale(tileSize / sprite.getTexture()->getSize().x, tileSize / sprite.getTexture()->getSize().y);
    incantations.push_back(std::move(sprite));
}

void Map::drawIncantations()
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();

    for (auto &incantation : incantations)
        window.draw(incantation);
}

/*std::shared_ptr<Tile> Map::getTileAtPosition(int x, int y)
{
    int relative_x = x / TILE_SIZE;
    int relative_y = y / TILE_SIZE;

    return this->getTileAtCoord(relative_x, relative_y);
}*/