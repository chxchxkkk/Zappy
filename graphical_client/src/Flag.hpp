/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Flag.hpp
*/

#ifndef ZAPPY_FLAG_HPP
#define ZAPPY_FLAG_HPP

#include <string>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "Position.hpp"

class Flag {
public:
    Flag(int id, const Position &pos, const std::string &teamName);

    void draw() const;
    int getId() const;
private:
    int id;
    Position pos;
    sf::Sprite sprite;
    static const std::vector<sf::Color> TEAM_COLORS;
};

#endif
