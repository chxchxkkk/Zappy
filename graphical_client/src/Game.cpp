/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include <thread>
#include "Game.hpp"

Game::Game(int, char *argv[]) : window(sf::VideoMode(width, height), "Zappy_client"),
                communicator(std::strtol(argv[1], &argv[1], 10), argv[2]),
                receiver(&Communicator::receiveData, &communicator),
                map(10, 10, window)
{
    communicator.sendData("GRAPHIC");
}

void Game::run()
{
    while (window.isOpen()) {
        this->processEvents();
        this->window.clear(sf::Color::Black);
        this->map.draw();
        this->window.display();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window.close();
    }
}