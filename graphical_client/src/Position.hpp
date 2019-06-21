/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Position.hpp
*/

#ifndef ZAPPY_POSITION_HPP
#define ZAPPY_POSITION_HPP

struct Position {
public:
    Position(int x, int y) :
        x(x),
        y(y)
    {}

    bool operator==(const Position &pos) const
    {
        return pos.x == x && pos.y == y;
    }

    int x;
    int y;
};

#endif
