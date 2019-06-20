/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Responsive.cpp
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include "Responsive.hpp"
#include "Singleton.hpp"

sf::Vector2f Responsive::calcTileSize(int mapWidth, int mapHeight)
{
    auto &w = SingleTon<sf::RenderWindow>::getInstance();

    if (mapWidth == 0 || mapHeight == 0)
        return {0, 0};
    return {w.getSize().x / static_cast<float>(mapWidth), w.getSize().y / static_cast<float>(mapHeight)};
}
