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
    player(player)
{
    if (!this->font.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("unable to load file assets/arial.ttf");
    float x_pos = 1340;
    float y_pos = 550;
    sf::Sprite background;

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/menu_ba.jpg"));
    background.setPosition(x_pos, y_pos);
    background.setColor(sf::Color(255, 255, 255, 150));
    background.setScale(0.3f, 0.4f);
    this->sprites.push_back(background);

    auto inventory = player.getInventory();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text quantity;
        std::string text = nameMap[it.first];
        quantity.setFont(this->font);

        text += " : " + std::to_string(it.second);
        resource.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(this->textureMap[it.first]));
        resource.setPosition(x_pos + 30, (i * 40) + 70 + y_pos);
        resource.setScale(0.15f, 0.15f);
        quantity.setString(text);
        quantity.setPosition(x_pos + 110, (i * 40) + 70 + y_pos);
        quantity.setFillColor(sf::Color::Black);
        this->textInfo.push_back(quantity);
        this->sprites.push_back(resource);
        i++;
    }
}

void PlayerInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    for (auto &it : this->sprites)
        window.draw(it);
    for (auto &it : this->textInfo)
        window.draw(it);
}
