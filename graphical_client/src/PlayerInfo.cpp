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
    sf::Sprite background;

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/menu_ba.jpg"));
    background.setPosition(x_pos, y_pos);
    background.setColor(sf::Color(255, 255, 255, 150));
    background.setScale(0.3f, 0.4f);
    sprites.push_back(background);

    initStrings();
}

void PlayerInfo::initStrings()
{
    auto inventory = player.getInventory();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text quantity;
        std::string text = nameMap[it.first];
        quantity.setFont(font);

        text += " : " + std::to_string(it.second);
        resource.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(textureMap[it.first]));
        resource.setPosition(x_pos + 30, (i * 40) + 70 + y_pos);
        resource.setScale(0.15f, 0.15f);
        quantity.setString(text);
        quantity.setPosition(x_pos + 110, (i * 40) + 70 + y_pos);
        quantity.setFillColor(sf::Color::Black);
        textInfo.push_back(quantity);
        sprites.push_back(resource);
        i++;
    }
}

void PlayerInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    for (auto &it : sprites)
        window.draw(it);
    for (auto &it : textInfo)
        window.draw(it);
}
