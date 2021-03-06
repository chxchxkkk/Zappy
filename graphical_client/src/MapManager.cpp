/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <memory>
#include <iostream>
#include "MapManager.hpp"

void MapManager::msz(const std::vector<std::string> &args)
{
    if (args.size() == 2)
        map = std::make_unique<Map>(std::stoi(args[0]), std::stoi(args[1]));
}

std::unique_ptr<Map> &MapManager::getMap()
{
    return map;
}

void MapManager::bct(const std::vector<std::string> &args)
{
    if (args.size() == 9) {
        auto position = parsePosition(std::vector<std::string>(args.begin(), args.begin() + 2));
        std::shared_ptr<Tile> &tile = map->getTileAtCoord(position.x, position.y);

        for (int i = 0; i <= 6; ++i)
            tile->setResource(static_cast<Resource>(i), std::stoi(args[2 + i]));
    }
}

void MapManager::pic(const std::vector<std::string> &args)
{
    map->addIncantationSprite(parsePosition(args));
}

void MapManager::pie(const std::vector<std::string> &args)
{
    map->removeIncantationSprite(parsePosition(args));
}

Position MapManager::parsePosition(const std::vector<std::string> &pos)
{
    return {std::stoi(pos[0]), std::stoi(pos[1])};
}
