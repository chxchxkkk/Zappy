/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Player.hpp
*/

#ifndef ZAPPY_PLAYER_HPP
#define ZAPPY_PLAYER_HPP

#include <vector>
#include <string>
#include "Position.hpp"
#include "Orientation.hpp"

class Player {
public:
    explicit Player(int id);

    int getId() const;
    void setPosition(const Position &newPos);
    void setOrientation(Orientation orientation);
private:
    int id;
    Position pos;
    Orientation orientation;
};

#endif
