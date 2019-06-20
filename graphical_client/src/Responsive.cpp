/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Responsive.cpp
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include "Responsive.hpp"
#include "Singleton.hpp"

float Responsive::calcTileSize(int mapWidth, int mapHeight)
{
    auto &w = SingleTon<sf::RenderWindow>::getInstance();

    if (mapWidth == 0 || mapHeight == 0)
        return 1;
    auto x = w.getSize().x / static_cast<float>(mapWidth);
    auto y = w.getSize().y / static_cast<float>(mapHeight);

    return std::min(x, y);
}
