/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerInfo.hpp
*/

#ifndef ZAPPY_PLAYERINFO_HPP
#define ZAPPY_PLAYERINFO_HPP

#include "Player.hpp"

class PlayerInfo {
public:
    explicit PlayerInfo(Player &player);
    void draw();
private:
    Player &player;
};

#endif
