/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        ~Game() = default;
        void run();
        void processEvents();

    private:
        unsigned int width = 1920;
        unsigned int height = 1080;
        sf::RenderWindow window;
};