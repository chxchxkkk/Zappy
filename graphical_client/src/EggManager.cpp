/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** EggManager.cpp
*/

#include <iostream>
#include "EggManager.hpp"
#include "Singleton.hpp"
#include "PlayerManager.hpp"

void EggManager::enw(const std::vector<std::string> &input)
{
    auto &playerManager = SingleTon<PlayerManager>::getInstance();
    int eggId = std::stoi(input[0]);
    int playerId = std::stoi(input[1]);
    auto pos = parsePosition({input.begin() + 2, input.end()});

    auto &player = playerManager.getPlayerById(playerId);
    eggs.emplace_back(eggId, pos, player.getTeamName());
}

Position EggManager::parsePosition(const std::vector<std::string> &pos)
{
    return {std::stoi(pos[0]), std::stoi(pos[1])};
}

void EggManager::draw()
{
    for (const auto &egg : eggs)
        egg.draw();
}
