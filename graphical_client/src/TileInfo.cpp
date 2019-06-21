/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "TileInfo.hpp"
#include "TextureLoader.hpp"
#include "Singleton.hpp"

TileInfo::TileInfo(Tile &tile)
{
    if (!this->font.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("unable to load file assets/arial.ttf");
    float x_pos = 1340;
    sf::Sprite background;

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/menu_ba.jpg"));
    background.setPosition(x_pos, 0);
    background.setColor(sf::Color(255, 255, 255, 150));
    background.setScale(0.3f, 0.4f);
    this->sprites.push_back(background);

    auto inventory = tile.getContent();
    int i = 0;
    for (auto &it : inventory) {
        sf::Sprite resource;
        sf::Text quantity;
        std::string text = nameMap[it.first];
        quantity.setFont(this->font);

        text += " : " + std::to_string(it.second);
        resource.setTexture(SingleTon<TextureLoader>::getInstance().getInstance(this->textureMap[it.first]));
        resource.setPosition(x_pos + 30, (i * 40) + 70);
        resource.setScale(0.15f, 0.15f);
        quantity.setString(text);
        quantity.setPosition(x_pos + 110, (i * 40) + 70);
        quantity.setFillColor(sf::Color::Black);
        this->textInfo.push_back(quantity);
        this->sprites.push_back(resource);
        i++;
    }
}

void TileInfo::draw()
{
    sf::RenderWindow &window = SingleTon<sf::RenderWindow>::getInstance();

    for (auto &it : this->sprites)
        window.draw(it);
    for (auto &it : this->textInfo)
        window.draw(it);
}
