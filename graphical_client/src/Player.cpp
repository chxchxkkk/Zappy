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
#include "PlayerManager.hpp"

static const std::vector<sf::Color> TEAM_COLORS = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta,
};

Player::Player(int id, const Position &pos, Orientation orientation, int level,
    const std::string &teamName) :
    id(id),
    pos(pos),
    orientation(orientation),
    level(level),
    teamName(teamName)
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
    pos.x = newPos.x;
    pos.y = newPos.y;
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
    const auto &teams = SingleTon<PlayerManager>::getInstance().getTeams();
    auto teamIndex = std::distance(teams.begin(), std::find(teams.begin(), teams.end(), this->teamName));

    characterSprite.setPosition((TILE_SIZE * pos.x) + 30, (TILE_SIZE * pos.y) + 30);
    characterSprite.setTextureRect(sf::IntRect((this->orientation - 1) * 100, 0, 100, 100));
    characterSprite.setColor(TEAM_COLORS[teamIndex % TEAM_COLORS.size()]);
    window.draw(this->characterSprite);
}
