/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include "Tile.hpp"
#include "Singleton.hpp"
#include "TextureLoader.hpp"

Tile::Tile(int x, int y) : x(x), y(y)
{

}

std::vector<sf::Sprite> &Tile::getSprites()
{
    this->sprites.clear();
    this->addSprites();
    return this->sprites;
}

void Tile::addResource(Resource type, int quantity)
{
    this->content[type] += quantity;
}

void Tile::removeResource(Resource type, int quantity)
{
    this->content[type] -= quantity;
    if (this->content[type] < 0)
        this->content[type] = 0;
}

const std::pair<int, int> Tile::getPosition() const
{
    return std::pair<int, int>(this->x, this->y);
}

void Tile::addSprites()
{
    int offset = 0;

    this->addGround();
    for (const auto &it : this->content) {
        if (it.second > 0) {
            this->addResourceSprite(it.first, offset);
            offset++;
        }
    }
}

void Tile::addGround()
{
    sf::Sprite sprite;

    sf::Texture &texture = SingleTon<TextureLoader>::getInstance().getInstance("assets/Grass.png");
    sprite.setTexture(texture);
    sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
    this->sprites.push_back(sprite);
}

void Tile::addResourceSprite(Resource type, int offset)
{
    sf::Sprite sprite;
    int x_offset = offset % 3;
    int y_offset = offset / 3;

    sf::Texture &texture = SingleTon<TextureLoader>::getInstance().getInstance(textureMap[type]);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    sprite.setPosition((x * TILE_SIZE) + 4 + (x_offset * 30), y * TILE_SIZE + 4 + (y_offset * 30));
    this->sprites.push_back(sprite);
}