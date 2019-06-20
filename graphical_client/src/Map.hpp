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
        std::shared_ptr<Tile> &getTileAtCoord(int x, int y);
        const std::vector<std::shared_ptr<Tile>> &getTiles() const;
        //        std::shared_ptr<Tile> getTileAtPosition(int x, int y);

    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        int width;
    public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    private:
    int height;
};

