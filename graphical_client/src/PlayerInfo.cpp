/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerInfo.cpp
*/

#include <iostream>
#include "PlayerInfo.hpp"
#include "TextureLoader.hpp"
#include "Singleton.hpp"

PlayerInfo::PlayerInfo(Player &player) :
    player(player),
    x_pos(1340),
    y_pos(550)
{
    if (!font.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("unable to load file assets/arial.ttf");

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/menu_ba.jpg"));
    background.setPosition(x_pos, y_pos);
    background.setColor(sf::Color(255, 255, 255, 150));
    background.setScale(0.3f, 0.4f);

    header.setFont(font);
    header.setFillColor(sf::Color::Black);
    header.setString("player inventory :");
    header.setPosition(x_pos + 20, y_pos + 15);

    playerLevel.setFont(font);
    playerLevel.setFillColor(sf::Color::Black);
    playerLevel.setString("player level : " + std::to_string(player.getLevel()));
    playerLevel.setPosition(x_pos + 110, y_pos + 55);
    initRows();
}

void PlayerInfo::initRows()
{
    auto inventory = player.getInventory();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text text;

        resource.setPosition(x_pos + 30, (i * 40) + 100 + y_pos);
        text.setPosition(x_pos + 110, (i * 40) + 100 + y_pos);
        inventoryRows.emplace_back(resource, text);
        updateRow(inventoryRows.back(), it);
        i++;
    }
}

void PlayerInfo::updateRow(std::pair<sf::Sprite, sf::Text> &row, const std::pair<Resource, int> &resourceText)
{
    std::string str = nameMap.at(resourceText.first);
    row.second.setFont(font);

    str += " : " + std::to_string(resourceText.second);
    row.first.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(textureMap.at(resourceText.first)));
    row.first.setScale(0.15f, 0.15f);
    row.second.setString(str);
    row.second.setFillColor(sf::Color::Black);
}

void PlayerInfo::update()
{
    auto &inventory = player.getInventory();
    int i = 0;

    playerLevel.setString("player level : " + std::to_string(player.getLevel()));
    if (inventory.size() == inventoryRows.size())
        for (auto &it : inventory) {
            updateRow(inventoryRows.at(i), it);
            ++i;
        }
}

void PlayerInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    update();
    window.draw(background);
    window.draw(header);
    window.draw(playerLevel);
    for (auto &it : inventoryRows) {
        window.draw(it.first);
        window.draw(it.second);
    }
}

int PlayerInfo::getPlayerId() const
{
    return player.getId();
}
