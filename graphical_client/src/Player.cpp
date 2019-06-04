/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.cpp
*/

#include <sstream>
#include "Player.hpp"

Player::Player(int id) :
    id(id),
    pos(0, 0),
    orientation(NORTH)
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
