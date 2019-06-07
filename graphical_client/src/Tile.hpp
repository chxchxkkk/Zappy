/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Resource.hpp"

#define TILE_SIZE 104

class Tile {
    public:
        Tile(int x, int y);
        ~Tile() = default;
        std::vector<sf::Sprite> &getSprites();
        void addResource(Resource type, int quantity);
        void setResource(Resource type, int quantity);
        void removeResource(Resource type, int quantity);
        const std::pair<int, int> getPosition() const;

    private:
        void addSprites();
        void addGround();
        void addResourceSprite(Resource type, int offset);

    private:
        int x;
        int y;
        std::vector<sf::Sprite> sprites;
        std::map<Resource, int> content = {
            {FOOD, 0},
            {LINEMATE, 0},
            {DERAUMERE, 0},
            {SIBUR, 0},
            {MENDIANE, 0},
            {PHIRAS, 0},
            {THYSTAME, 0},
        };
    public:
    const std::map<Resource, int> &getContent() const;

    private:
    std::map<Resource, std::string> textureMap = {
            {FOOD, "assets/Food.png"},
            {LINEMATE, "assets/Linemate.png"},
            {DERAUMERE, "assets/Deraumere.png"},
            {SIBUR, "assets/Sibur.png"},
            {MENDIANE, "assets/Mendiane.png"},
            {PHIRAS, "assets/Phiras.png"},
            {THYSTAME, "assets/Thystame.png"},
        };
};