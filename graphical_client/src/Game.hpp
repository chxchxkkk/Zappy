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

class Game {
    public:
        Game(int argc, char *argv[]);
        ~Game() = default;
        void run();
        void processEvents();

    private:
        unsigned int width = 1920;
        unsigned int height = 1080;
        sf::RenderWindow window;
        Communicator communicator;
        std::thread receiver;
        Map map;
};