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

    Position(const Position &position) :
    x(position.x),
    y(position.y)
    {}

    Position &operator=(const Position &position) {
        this->x = position.x;
        this->y = position.y;
        return *this;
    }

    int x;
    int y;
};

#endif
