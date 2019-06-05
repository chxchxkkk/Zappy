/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** World.hpp
*/

#ifndef ZAPPY_WORLD_HPP
#define ZAPPY_WORLD_HPP

#include <map>
#include <vector>
#include <functional>
#include "Player.hpp"
#include "PlayerManager.hpp"

class World {
public:
    World();
private:
    PlayerManager playerManager;
    std::map<std::string, std::function<void(const std::vector<std::string> &)>> actions;
};

#endif
