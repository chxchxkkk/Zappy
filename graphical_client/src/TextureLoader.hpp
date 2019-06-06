/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureLoader {
    public:
        TextureLoader() = default;
        ~TextureLoader() = default;
        sf::Texture &getInstance(std::string path);
    private:
        std::map<std::string, sf::Texture> textures;
};

