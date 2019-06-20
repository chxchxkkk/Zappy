/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include <thread>
#include "Game.hpp"
#include "String.hpp"
#include "Singleton.hpp"
#include "Responsive.hpp"

Game::Game(int, char *argv[]) :
    communicator(std::strtol(argv[1], &argv[1], 10), argv[2]),
    receiver(&Communicator::receiveData, &communicator),
    dispatcher(playerManager, mapManager)
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    window.create(sf::VideoMode(1920, 1080), "Zappy Graphique");
    communicator.sendData("GRAPHIC");
}

void Game::run()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    if (window.isOpen())
        std::cout << window.isOpen() << std::endl;
    while (window.isOpen()) {
        this->processEvents();
        this->processCommands();
        window.clear(sf::Color::Black);
        this->draw();
        window.display();
    }
}

void Game::processEvents()
{
    sf::Event event;
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                this->selectTile(event);
            }
        }
    }
}

void Game::processCommands()
{
    std::string data;

    while (!(data = this->communicator.popData()).empty()) {
        std::cout << "received : " << data << std::endl;
        std::vector<std::string> argList = String::split(data, " ");
        if (argList.empty())
            continue;
        this->dispatcher.dispatchCommand(argList);
    }
}

void Game::draw()
{
    if (this->mapManager.getMap() != nullptr) {
        this->mapManager.getMap()->draw();
    }
    if (this->selectedTile)
        this->tileInfo->draw();
    this->playerManager.draw();
}

Game::~Game()
{
    this->communicator.setRunning(false);
    this->receiver.join();
}

void Game::selectTile(sf::Event &event)
{
    for (const auto &tile : mapManager.getMap()->getTiles())
        if (tile->getSprites()[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            selectedTile = tile;
            this->tileInfo = std::make_unique<TileInfo>(*this->selectedTile);
        }
}

void Game::displayTileInfo()
{
    Position position = selectedTile->getPosition();

    std::cout << "selected at pos : x " << position.x << " y " << position.y << std::endl;
}