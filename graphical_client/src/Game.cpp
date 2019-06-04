/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "Game.hpp"

Game::Game() : window(sf::VideoMode(width, height), "Zappy_client")
{}

void Game::run()
{
    while (window.isOpen())
    {
        this->processEvents();
        this->window.clear(sf::Color::Black);
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
