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

void EggManager::eht(const std::vector<std::string> &input)
{
    int id = std::stoi(input[0]);
    auto it = std::find_if(eggs.begin(), eggs.end(), [&id](const Egg &egg) {
        return id == egg.getId();
    });

    if (it == eggs.end())
        return;
    flags.emplace_back(id, it->getPosition(), it->getTeamName());
    eggs.erase(it);
}

void EggManager::ebo(const std::vector<std::string> &input)
{
    int id = std::stoi(input[0]);

    flags.erase(std::remove_if(flags.begin(), flags.end(), [&id](const Flag &flag) {
        return flag.getId() == id;
    }), flags.end());
}

Position EggManager::parsePosition(const std::vector<std::string> &pos)
{
    return {std::stoi(pos[0]), std::stoi(pos[1])};
}

void EggManager::draw()
{
    for (const auto &egg : eggs)
        egg.draw();
    for (const auto &flag : flags)
        flag.draw();
}
