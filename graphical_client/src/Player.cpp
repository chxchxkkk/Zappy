/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.cpp
*/

#include <utility>
#include "Player.hpp"

Player::Player(int id, const Position &pos, Orientation orientation, int level, std::string teamName) :
    id(id),
    pos(pos),
    orientation(orientation),
    level(level),
    teamName(std::move(teamName))
{
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
