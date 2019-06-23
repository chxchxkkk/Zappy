/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerInfo.hpp
*/

#ifndef ZAPPY_PLAYERINFO_HPP
#define ZAPPY_PLAYERINFO_HPP

#include "Player.hpp"

class PlayerInfo {
public:
    explicit PlayerInfo(Player &player);
    void draw();
    int getPlayerId() const;
private:
    void initRows();
    void updateRow(std::pair<sf::Sprite, sf::Text> &row, const std::pair<Resource, int> &resourceText);
    void update();

    Player &player;
    int x_pos;
    int y_pos;
    sf::Sprite background;
    sf::Text header;
    std::vector<std::pair<sf::Sprite, sf::Text>> inventoryRows;
    sf::Text playerLevel;
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

#endif
