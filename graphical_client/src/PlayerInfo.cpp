/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerInfo.cpp
*/

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

    initStrings();
}

void PlayerInfo::initStrings()
{
    auto inventory = player.getInventory();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text text;
        std::string str = nameMap[it.first];
        text.setFont(font);

        str += " : " + std::to_string(it.second);
        resource.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(textureMap[it.first]));
        resource.setPosition(x_pos + 30, (i * 40) + 70 + y_pos);
        resource.setScale(0.15f, 0.15f);
        text.setString(str);
        text.setPosition(x_pos + 110, (i * 40) + 70 + y_pos);
        text.setFillColor(sf::Color::Black);
        rows.emplace_back(resource, text);
        i++;
    }
}

void PlayerInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    window.draw(background);
    for (auto &it : rows) {
        window.draw(it.first);
        window.draw(it.second);
    }
}
