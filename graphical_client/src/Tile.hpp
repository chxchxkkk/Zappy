/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>

#define TILE_SIZE 104

class Tile {
    public:
        Tile(int x, int y);
        ~Tile() = default;
        sf::Sprite &getSprite();

    private:
        int x;
        int y;
        sf::Sprite sprite;
        sf::Texture texture;
};

