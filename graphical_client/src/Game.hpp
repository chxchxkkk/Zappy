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

class Game {
    public:
        Game(int argc, char *argv[]);
        ~Game();
        void run();
        void draw();
        void processEvents();
        void processCommands();

    private:
        unsigned int width = 1920;
        unsigned int height = 1080;
        Communicator communicator;
        std::thread receiver;
        PlayerManager playerManager;
        MapManager mapManager;
        Dispatcher dispatcher;
};