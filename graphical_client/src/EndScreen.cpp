/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** EndScreen.cpp
*/

#include "EndScreen.hpp"
#include "Singleton.hpp"
#include "TextureLoader.hpp"

EndScreen::EndScreen(const std::vector<std::string> &input)
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();

    if (!font.loadFromFile("assets/arial.ttf"))
        throw std::runtime_error("unable to load file assets/arial.ttf");

    text.setPosition(window.getSize().x / 2.0f - 60, window.getSize().y / 2.0f);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(input[0] + " won");

    background.setTexture(SingleTon<TextureLoader>::getInstance().getInstance("assets/end_screen.jpg"));
    background.setPosition(0, 0);
    background.setScale(window.getSize().x / static_cast<float>(background.getTexture()->getSize().x), window.getSize().y /
        static_cast<float>(background.getTexture()->getSize().y));
}

void EndScreen::start()
{
    auto &window = SingleTon<sf::RenderWindow>::getInstance();

    while (true) {
        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(text);
        window.display();
        sf::Event event{};

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                exit(0);
            }
    }
}
