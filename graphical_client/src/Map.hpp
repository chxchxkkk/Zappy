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
    int getWidth() const;
    int getHeight() const;
    void addIncantationSprite(const Position &pos);
    void drawIncantations();

private:
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<sf::Sprite> incantations;
    int width;
    int height;
    float tileSize;
};

