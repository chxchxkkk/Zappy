/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerManager.cpp
*/

#include <algorithm>
#include "PlayerManager.hpp"

void PlayerManager::pnw(const std::vector<std::string> &input)
{
    Position pos(std::stoi(input[1]), std::stoi(input[2]));
    auto orientation = static_cast<Orientation>(std::stoi(input[3]));

    players.emplace_back(parseId(input[0]), pos, orientation, std::stoi(input[4]), input[5]);
}

void PlayerManager::ppo(const std::vector<std::string> &input)
{
    auto player = getPlayerById(parseId(input[0]));

    player.setPosition(Position(std::stoi(input[1]), std::stoi(input[2])));
    player.setOrientation(static_cast<Orientation>(std::stoi(input[3])));
}

Player &PlayerManager::getPlayerById(int id)
{
    return *std::find_if(players.begin(), players.end(), [id](const Player &player) {
        return player.getId() == id;
    });
}

int PlayerManager::parseId(const std::string &s) const
{
    if (s[0] == '#')
        return std::stoi(s.substr(1));
    return std::stoi(s);
}
