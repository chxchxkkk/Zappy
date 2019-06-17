/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.cpp
*/

#include <utility>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.hpp"
#include "Singleton.hpp"
#include "TextureLoader.hpp"
#include "Tile.hpp"

Player::Player(int id, const Position &pos, Orientation orientation, int level, std::string teamName) :
    id(id),
    pos(pos),
    orientation(orientation),
    level(level),
    teamName(std::move(teamName))
{
    inventory[FOOD] = 0;
    inventory[LINEMATE] = 0;
    inventory[DERAUMERE] = 0;
    inventory[SIBUR] = 0;
    inventory[MENDIANE] = 0;
    inventory[PHIRAS] = 0;
    inventory[THYSTAME] = 0;
    characterSprite.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/Character.png"));
    characterSprite.setPosition((TILE_SIZE * pos.x) + 30, (TILE_SIZE * pos.y) + 30);
    characterSprite.setScale(0.5f, 0.5f);
}

int Player::getId() const
{
    return id;
}

void Player::setPosition(const Position &newPos)
{
    std::cout << " " << pos.x << " " << pos.y << std::endl;
    pos.x = newPos.x;
    pos.y = newPos.y;
    std::cout << " " << pos.x << " " << pos.y << std::endl;
}

void Player::setOrientation(Orientation newOrientation)
{
    orientation = newOrientation;
}

void Player::setLevel(int newLevel)
{
    level = newLevel;
}

void Player::setResource(Resource type, int quantity)
{
    this->inventory[type] = quantity;
}

void Player::setIncanting(bool newStatus)
{
    this->incanting = newStatus;
}

bool Player::isIncanting() const
{
    return this->incanting;
}

const Position &Player::getPosition() const
{
    return this->pos;
}

void Player::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    std::cout << "X : " << pos.x << " Y: " << pos.y << std::endl;
    characterSprite.setPosition((TILE_SIZE * pos.x) + 30, (TILE_SIZE * pos.y) + 30);
    window.draw(this->characterSprite);
}
