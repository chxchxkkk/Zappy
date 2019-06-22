/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** EndScreen.hpp
*/

#ifndef ZAPPY_ENDSCREEN_HPP
#define ZAPPY_ENDSCREEN_HPP

#include <SFML/Graphics.hpp>

class EndScreen {
public:
    explicit EndScreen(const std::vector<std::string> &input);
    void start();
private:
    sf::Sprite background;
    sf::Text text;
    sf::Font font;
};

#endif
