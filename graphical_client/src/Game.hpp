/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include "communicator.hpp"
#include "Map.hpp"
#include "PlayerManager.hpp"
#include "MapManager.hpp"
#include "Dispatcher.hpp"
#include "TileInfo.hpp"

class Game {
    public:
        Game(int argc, char *argv[]);
        ~Game();
        void run();
        void draw();
        void processEvents();
        void processCommands();
        void selectTile(sf::Event &event);
        void displayTileInfo();

    private:
        unsigned int width = 1920;
        unsigned int height = 1080;
        Communicator communicator;
        std::unique_ptr<sf::View> view;
        std::shared_ptr<Tile> selectedTile = nullptr;
        std::thread receiver;
        Dispatcher dispatcher;
        sf::View mapView;
        sf::View menuView;
        std::unique_ptr<TileInfo> tileInfo = nullptr;
    void drawFocus(std::shared_ptr<Tile> &tile);
};