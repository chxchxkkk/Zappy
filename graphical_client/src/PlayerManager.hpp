/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** PlayerManager.hpp
*/

#ifndef ZAPPY_PLAYERMANAGER_HPP
#define ZAPPY_PLAYERMANAGER_HPP

#include <memory>
#include <vector>
#include "Player.hpp"

class PlayerManager {
public:
    PlayerManager() = default;
    Player &getPlayerById(int id);

    void ppo(const std::vector<std::string> &input);
    void pnw(const std::vector<std::string> &input);
    void plv(const std::vector<std::string> &input);
    void pin(const std::vector<std::string> &input);

    int parseId(const std::string &s) const;
private:
    std::vector<Player> players;
};

#endif
