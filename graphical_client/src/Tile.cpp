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
#include "Position.hpp"
#include "Responsive.hpp"

Tile::Tile(int x, int y, float size) : x(x), y(y), size(size)
{
}

std::vector<sf::Sprite> &Tile::getSprites()
{
    sprites.clear();
    addSprites();
    return sprites;
}

void Tile::addResource(Resource type, int quantity)
{
    content[type] += quantity;
}

void Tile::removeResource(Resource type, int quantity)
{
    content[type] -= quantity;
    if (content[type] < 0)
        content[type] = 0;
}

Position Tile::getPosition() const
{
    return {x, y};
}

void Tile::addSprites()
{
    int offset = 0;

    addGround();
    for (const auto &it : content) {
        if (it.second > 0) {
            addResourceSprite(it.first, offset);
            offset++;
        }
    }
}

void Tile::addGround()
{
    sf::Sprite sprite;

    sf::Texture &texture = SingleTon<TextureLoader>::getInstance().getInstance("assets/Grass.png");
    sprite.setTexture(texture);
    sprite.setScale(Responsive::getScale(size, texture.getSize()));
    sprite.setPosition(x * size, y * size);
    sprites.push_back(sprite);
}

void Tile::addResourceSprite(Resource type, int offset)
{
    sf::Sprite sprite;
    int x_offset = offset % 3;
    int y_offset = offset / 3;

    sf::Texture &texture = SingleTon<TextureLoader>::getInstance().getInstance(textureMap[type]);
    sprite.setTexture(texture);
    sprite.setScale(Responsive::getScale(size / 5, texture.getSize()));
    std::cout << size << std::endl;
    sprite.setPosition((x * size) + size / 25.0f + (x_offset * size / 3), y * size + size / 25.0f + (y_offset * size / 3));
    sprites.push_back(sprite);
}

void Tile::setResource(Resource type, int quantity)
{
    content[type] = quantity;
}

const std::map<Resource, int> &Tile::getContent() const
{
    return content;
}
