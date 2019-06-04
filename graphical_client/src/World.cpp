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
        {"ppo", [this](const std::vector<std::string> &input) { playerManager.ppo(input); }}
    };
}
