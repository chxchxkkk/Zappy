/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <vector>
#include <memory>
#include "Tile.hpp"

class Map {
    public:
        Map(int width, int height);
        ~Map() = default;
        void draw();
        std::unique_ptr<Tile> &getTileAtCoord(int x, int y);

    private:
        std::vector<std::unique_ptr<Tile>> tiles;
        int width;
        int height;
};

