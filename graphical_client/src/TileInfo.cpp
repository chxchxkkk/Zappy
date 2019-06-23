/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include <iostream>
#include "TileInfo.hpp"
#include "TextureLoader.hpp"
#include "Singleton.hpp"
#include "PlayerManager.hpp"

TileInfo::TileInfo(Tile &tile) :
    tile(tile)
{
    if (!font.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("unable to load file assets/arial.ttf");
    float x_pos = 1340;

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/menu_ba.jpg"));
    background.setPosition(x_pos, 0);
    background.setColor(sf::Color(255, 255, 255, 150));
    background.setScale(0.3f, 0.4f);

    nbPlayersText.setFont(font);
    nbPlayersText.setPosition(x_pos + 10, 10);
    nbPlayersText.setFillColor(sf::Color::Black);

    auto inventory = tile.getContent();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text text;

        resource.setPosition(x_pos + 30, (i * 40) + 70);
        text.setPosition(x_pos + 110, (i * 40) + 70);
        rows.emplace_back(resource, text);
        updateRow(rows.back(), it);
        i++;
    }
}

void TileInfo::updateNbPlayerText()
{
    int i = 0;
    const auto &players = SingleTon<PlayerManager>::getInstance().getPlayers();

    for (const auto &player : players)
        if (player.getPosition() == tile.getPosition())
            ++i;
    nbPlayersText.setString("Nb players : " + std::to_string(i));
}

void TileInfo::updateRow(std::pair<sf::Sprite, sf::Text> &row, const std::pair<Resource, int> &resourceText)
{
    std::string str = nameMap.at(resourceText.first);
    row.second.setFont(font);

    str += " : " + std::to_string(resourceText.second);
    row.first.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(textureMap.at(resourceText.first)));
    row.first.setScale(0.15f, 0.15f);
    row.second.setString(str);
    row.second.setFillColor(sf::Color::Black);
}

void TileInfo::update()
{
    auto &inventory = tile.getContent();
    int i = 0;

    updateNbPlayerText();
    if (inventory.size() == rows.size())
        for (auto &it : inventory) {
            updateRow(rows.at(i), it);
            ++i;
        }
}
void TileInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    update();
    window.draw(background);
    window.draw(nbPlayersText);
    for (auto &it : rows) {
        window.draw(it.first);
        window.draw(it.second);
    }
}
