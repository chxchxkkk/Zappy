/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Responsive.hpp
*/

#ifndef ZAPPY_RESPONSIVE_HPP
#define ZAPPY_RESPONSIVE_HPP

class Responsive {
public:
    static float calcTileSize(int mapWidth, int mapHeight);

    template <typename T>
    static sf::Vector2f getScale(float size, const sf::Vector2<T> &textureSize)
    {
        return {size / textureSize.x, size / textureSize.y};
    }
};

#endif
