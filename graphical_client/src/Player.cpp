/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.cpp
*/

#include <utility>
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
    sf::Sprite characterSprite;

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
    this->sprites.push_back(characterSprite);
}

int Player::getId() const
{
    return id;
}

void Player::setPosition(const Position &newPos)
{
    pos = newPos;
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

    for (auto &it : this->sprites) {
        window.draw(it);
    }
}
