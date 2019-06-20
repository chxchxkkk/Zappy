/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Dispatcher.cpp
*/

#include <iostream>
#include <functional>
#include "Dispatcher.hpp"

Dispatcher::Dispatcher(PlayerManager &playerManager, MapManager &mapManager) :
    playerManager(playerManager),
    mapManager(mapManager)
{
    actions = {
        {"pnw", [this](const std::vector<std::string> &input) {this->playerManager.pnw(input);}},
        {"ppo", [this](const std::vector<std::string> &input) {this->playerManager.ppo(input);}},
        {"plv", [this](const std::vector<std::string> &input) {this->playerManager.plv(input);}},
        {"pin", [this](const std::vector<std::string> &input) {this->playerManager.pin(input);}},
        {"tna", [this](const std::vector<std::string> &input) {this->playerManager.tna(input);}},
        {"pdi", [this](const std::vector<std::string> &input) {this->playerManager.pdi(input);}},
        {"msz", [this](const std::vector<std::string> &input) {this->mapManager.msz(input);}},
        {"bct", [this](const std::vector<std::string> &input) {this->mapManager.bct(input);}},
    };
}

void Dispatcher::dispatchCommand(const std::vector<std::string> &arg)
{
    try {
        if (this->actions.find(arg[0]) != this->actions.end())
            this->actions[arg[0]](
                std::vector<std::string>(arg.begin() + 1, arg.end()));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
