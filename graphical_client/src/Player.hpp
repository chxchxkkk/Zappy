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
#include <map>
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Orientation.hpp"
#include "Resource.hpp"

class Player {
public:
    Player(int id, const Position &pos, Orientation orientation, int level, std::string teamName);

    int getId() const;
    void setPosition(const Position &newPos);
    void setOrientation(Orientation orientation);
    void setLevel(int newLevel);
    void setResource(Resource type, int quantity);
    bool isIncanting() const;
    void setIncanting(bool);
    const Position &getPosition() const;
    void draw();

private:
    int id;
    Position pos;
    Orientation orientation;
    int level;
    std::string teamName;
    std::map<Resource, int> inventory;
    bool incanting = false;
    std::vector<sf::Sprite> sprites;
};

#endif
