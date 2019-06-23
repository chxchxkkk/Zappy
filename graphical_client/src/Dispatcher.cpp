/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Dispatcher.cpp
*/

#include <iostream>
#include <functional>
#include "Dispatcher.hpp"
#include "EndScreen.hpp"
#include "Singleton.hpp"
#include "EggManager.hpp"

Dispatcher::Dispatcher()
{
    auto &playerManager = SingleTon<PlayerManager>::getInstance();
    auto &mapManager = SingleTon<MapManager>::getInstance();
    auto &eggManager = SingleTon<EggManager>::getInstance();

    actions = {
        {"pnw", [&](const std::vector<std::string> &input) { playerManager.pnw(input); }},
        {"ppo", [&](const std::vector<std::string> &input) { playerManager.ppo(input); }},
        {"plv", [&](const std::vector<std::string> &input) { playerManager.plv(input); }},
        {"pin", [&](const std::vector<std::string> &input) { playerManager.pin(input); }},
        {"tna", [&](const std::vector<std::string> &input) { playerManager.tna(input); }},
        {"pdi", [&](const std::vector<std::string> &input) { playerManager.pdi(input); }},
        {"pbc", [&](const std::vector<std::string> &input) { playerManager.pbc(input); }},
        {"msz", [&](const std::vector<std::string> &input) { mapManager.msz(input); }},
        {"bct", [&](const std::vector<std::string> &input) { mapManager.bct(input); }},
        {"pic", [&](const std::vector<std::string> &input) { mapManager.pic(input); }},
        {"pie", [&](const std::vector<std::string> &input) { mapManager.pie(input); }},
        {"enw", [&](const std::vector<std::string> &input) { eggManager.enw(input); }},
        {"eht", [&](const std::vector<std::string> &input) { eggManager.eht(input); }},
        {"ebo", [&](const std::vector<std::string> &input) { eggManager.ebo(input); }},
        {"seg", [&](const std::vector<std::string> &input) { seg(input); }},
    };
}

void Dispatcher::dispatchCommand(const std::vector<std::string> &arg)
{
    try {
        if (actions.find(arg[0]) != actions.end())
            actions[arg[0]](
                std::vector<std::string>(arg.begin() + 1, arg.end()));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Dispatcher::seg(const std::vector<std::string> &input)
{
    EndScreen endScreen(input);

    endScreen.start();
}
