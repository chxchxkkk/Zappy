/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Player.hpp"

class TileInfo {
public:
    explicit TileInfo(Tile &tile);
    ~TileInfo() = default;
    void draw();

private:
    void updateRow(std::pair<sf::Sprite, sf::Text> &row, const std::pair<Resource, int> &resourceText);
    void update();
    void updateNbPlayerText();

    Tile &tile;
    std::vector<std::pair<sf::Sprite, sf::Text>> rows;
    sf::Text nbPlayersText;
    sf::Sprite background;
    sf::Font font;
    std::map<Resource, std::string> textureMap = {
        {FOOD,      "assets/Food.png"},
        {LINEMATE,  "assets/Linemate.png"},
        {DERAUMERE, "assets/Deraumere.png"},
        {SIBUR,     "assets/Sibur.png"},
        {MENDIANE,  "assets/Mendiane.png"},
        {PHIRAS,    "assets/Phiras.png"},
        {THYSTAME,  "assets/Thystame.png"},
    };
    std::map<Resource, std::string> nameMap = {
        {FOOD,      "Food"},
        {LINEMATE,  "Linemate"},
        {DERAUMERE, "Deraumere"},
        {SIBUR,     "Sibur"},
        {MENDIANE,  "Mendiane"},
        {PHIRAS,    "Phiras"},
        {THYSTAME,  "Thystame"},
    };
};
