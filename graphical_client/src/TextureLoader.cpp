/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Created by abel,
*/

#include "TextureLoader.hpp"

sf::Texture &TextureLoader::getInstance(std::string path)
{
    if (this->textures.find(path) != this->textures.end())
        return this->textures[path];
    else {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::runtime_error(("file " + path + " not found").c_str());
        this->textures[path] = texture;
        return this->textures[path];
    }
}
