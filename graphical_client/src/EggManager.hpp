/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** EggManager.hpp
*/

#ifndef ZAPPY_EGGMANAGER_HPP
#define ZAPPY_EGGMANAGER_HPP

#include <vector>
#include <string>
#include "Egg.hpp"
#include "Position.hpp"
#include "Flag.hpp"

class EggManager {
public:
    void enw(const std::vector<std::string> &input);
    void eht(const std::vector<std::string> &input);
    void ebo(const std::vector<std::string> &input);

    void draw();
private:
    Position parsePosition(const std::vector<std::string> &pos);
    std::vector<Egg> eggs;
    std::vector<Flag> flags;
};

#endif
