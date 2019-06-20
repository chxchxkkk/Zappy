/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <memory>
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

    view = std::make_unique<sf::View>(sf::FloatRect(0, 0, 1000, 600));
    view->reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(*view);
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
    int movePower = 15;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseWheelScrolled)
            view->zoom(1 - event.mouseWheelScroll.delta / 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view->move(-movePower, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view->move(movePower, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view->move(0, -movePower);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view->move(0, movePower);
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                selectTile();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            selectedTile = nullptr;
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
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    window.setView(*view);
    if (SingleTon<MapManager>::getInstance().getMap() != nullptr)
        SingleTon<MapManager>::getInstance().getMap()->draw();
    SingleTon<PlayerManager>::getInstance().draw();
    if (selectedTile) {
        window.setView(window.getDefaultView());
        tileInfo->draw();
        window.setView(*view);
        drawFocus(selectedTile);
    }
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

void Game::selectTile()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    auto pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    for (const auto &tile : SingleTon<MapManager>::getInstance().getMap()->getTiles())
        if (tile->getSprites()[0].getGlobalBounds().contains(worldPos.x, worldPos.y)) {
            selectedTile = tile;
            tileInfo = std::make_unique<TileInfo>(*selectedTile);
        }
}

void Game::displayTileInfo()
{
    Position position = selectedTile->getPosition();

    std::cout << "selected at pos : x " << position.x << " y " << position.y << std::endl;
}
