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

    int x;
    int y;
};

#endif
