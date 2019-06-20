#include <memory>
#include <iostream>

/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "MapManager.hpp"

void MapManager::msz(const std::vector<std::string> &args)
{
    if (args.size() == 2)
        this->map = std::make_unique<Map>(std::stoi(args[0]), std::stoi(args[1]));
}

std::unique_ptr<Map> &MapManager::getMap()
{
    return this->map;
}

void MapManager::bct(const std::vector<std::string> &args)
{
    std::cout << args[2] << std::endl;
    if (args.size() == 9) {
        std::pair<int, int> position = parsePosition(std::vector<std::string>(args.begin(), args.begin() + 2));
        std::shared_ptr<Tile> &tile = this->map->getTileAtCoord(position.first, position.second);

        for (int i = 0; i <= 6; ++i) {
            tile->setResource(static_cast<Resource>(i), std::stoi(args[2 + i]));
        }
    }
}

std::pair<int, int> MapManager::parsePosition(const std::vector<std::string> &pos)
{
    return {std::stoi(pos[0]), std::stoi(pos[1])};
}