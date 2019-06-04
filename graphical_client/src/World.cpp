/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** World.cpp
*/

#include "World.hpp"

World::World()
{
    actions = {
        {"pnw", [this](const std::vector<std::string> &input) { playerManager.pnw(input); }},
        {"ppo", [this](const std::vector<std::string> &input) { playerManager.ppo(input); }},
        {"plv", [this](const std::vector<std::string> &input) { playerManager.plv(input); }},
    };
}
