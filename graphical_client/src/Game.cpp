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
#include "EggManager.hpp"

Game::Game(int, char *argv[]) :
    communicator(static_cast<uint16_t>(std::strtol(argv[1], &argv[1], 10)), argv[2]),
    receiver(&Communicator::receiveData, &communicator),
    dispatcher()
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
    float zoomAmount = 1.1f;

    sendInventoryEachSeconds();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0)
                zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, (1.f / zoomAmount));
            else if (event.mouseWheelScroll.delta < 0)
                zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, zoomAmount);
        }

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            selectedTile = nullptr;
            SingleTon<PlayerManager>::getInstance().removeInfo();
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
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    window.setView(*view);
    if (SingleTon<MapManager>::getInstance().getMap() != nullptr)
        SingleTon<MapManager>::getInstance().getMap()->draw();
    SingleTon<EggManager>::getInstance().draw();
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
    auto &playerManager = SingleTon<PlayerManager>::getInstance();
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();
    auto pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    for (const auto &tile : SingleTon<MapManager>::getInstance().getMap()->getTiles()) {
        if (tile->getSprites().at(0).getGlobalBounds().contains(worldPos.x, worldPos.y)) {
            selectedTile = tile;
            tileInfo = std::make_unique<TileInfo>(*selectedTile);
            playerManager.updatePlayerInfo(selectedTile->getPosition());
            break;
        }
    }
}

void Game::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom)
{
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    view->zoom(zoom);
    window.setView(*view);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    view->move(offsetCoords);
    window.setView(*view);
}

void Game::sendInventoryEachSeconds()
{
    static auto prevTime = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::now();
    auto &playerManager = SingleTon<PlayerManager>::getInstance();
    std::chrono::duration<float> duration = time - prevTime;

    if (duration.count() > 1) {
        prevTime = time;
        if (playerManager.isInfo()) {
            std::cout << "send to player : " + std::to_string(playerManager.getPlayerInfoId()) << std::endl;
            communicator.sendData("pin " + std::to_string(playerManager.getPlayerInfoId()));
        }
    }
}
