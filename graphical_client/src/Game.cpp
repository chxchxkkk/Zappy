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
    communicator(static_cast<uint16_t>(std::strtol(argv[1], &argv[1], 10)), argv[2]),
    receiver(&Communicator::receiveData, &communicator),
    dispatcher(SingleTon<PlayerManager>::getInstance(),
        SingleTon<MapManager>::getInstance())
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    window.create(sf::VideoMode(1920, 1080), "Zappy Graphic");
    communicator.sendData("GRAPHIC");
}

Game::~Game()
{
    communicator.setRunning(false);
    receiver.join();
}

void Game::run()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    while (window.isOpen()) {
        processEvents();
        processCommands();
        window.clear(sf::Color::Black);
        draw();
        window.display();
    }
}

void Game::processEvents()
{
    sf::Event event{};
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                selectTile(event);
            }
        }
    }
}

void Game::processCommands()
{
    std::string data;

    while (!(data = communicator.popData()).empty()) {
        std::cout << "received : " << data << std::endl;
        std::vector<std::string> argList = String::split(data, " ");
        if (argList.empty())
            continue;
        dispatcher.dispatchCommand(argList);
    }
}

void Game::draw()
{
    if (SingleTon<MapManager>::getInstance().getMap() != nullptr)
        SingleTon<MapManager>::getInstance().getMap()->draw();
    if (selectedTile) {
        tileInfo->draw();
        drawFocus(selectedTile);
    }
    SingleTon<PlayerManager>::getInstance().draw();
}

void Game::drawFocus(std::shared_ptr<Tile> &tile)
{
    auto &map = SingleTon<MapManager>::getInstance().getMap();
    auto size = Responsive::calcTileSize(map->getWidth(), map->getHeight());
    sf::RectangleShape shape;

    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Red);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(tile->getSprites().at(0).getPosition());
    shape.setSize(sf::Vector2f(size, size));
    SingleTon<sf::RenderWindow>::getInstance().draw(shape);
}

void Game::selectTile(sf::Event &event)
{
    for (const auto &tile : SingleTon<MapManager>::getInstance().getMap()->getTiles())
        if (tile->getSprites()[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            selectedTile = tile;
            tileInfo = std::make_unique<TileInfo>(*selectedTile);
        }
}

void Game::displayTileInfo()
{
    Position position = selectedTile->getPosition();

    std::cout << "selected at pos : x " << position.x << " y " << position.y << std::endl;
}
