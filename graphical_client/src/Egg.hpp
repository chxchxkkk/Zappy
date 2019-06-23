/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Egg.hpp
*/

#ifndef ZAPPY_EGG_HPP
#define ZAPPY_EGG_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "TextureLoader.hpp"

class Egg {
public:
    Egg(int id, const Position &pos, const std::string &teamName);

    void draw() const;
    int getId() const;
    const std::string &getTeamName() const;
    const Position &getPosition() const;
private:
    int id;
    Position pos;
    std::string teamName;
    sf::Sprite sprite;
    static const std::vector<sf::Color> TEAM_COLORS;
};

#endif
